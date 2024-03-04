/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2023 QuiMir <2546670299@qq.com>.
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 ** http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 **/

#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/file_path_system.h"
#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/json_type/json_type.h"

FileWriteSystem &FileWriteSystem::GetInstance(QString log_file)
{
    return Instance(log_file);
}

void FileWriteSystem::CustomMessageHandler(QtMsgType type,const QMessageLogContext& context,const QString &msg)
{
    GetInstance().GetLogFile().open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream text_stream(&GetInstance().GetLogFile());

    switch(type)
    {
    case QtDebugMsg:
        text_stream<<"Debug: "<<msg<<"\n";
        break;
    case QtWarningMsg:
        text_stream<<"Warning: "<<msg<<"\n";
        break;
    case QtCriticalMsg:
        text_stream<<"Critical: "<<msg<<"\n";
        break;
    case QtFatalMsg:
        text_stream<<"Fatal: "<<msg<<"\n";
        abort();
    case QtInfoMsg:
        break;
    }

    GetInstance().GetLogFile().close();
}

void FileWriteSystem::OutMessage(MessageTypeBit type, const QString out_string)
{
    if(type==MessageTypeBit::kDebug)
    {
        qDebug()<<"Current Date and Time:"<<FileWriteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type==MessageTypeBit::kWarning)
    {
        qWarning()<<"Current Date and Time:"<<FileWriteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type==MessageTypeBit::kCritical)
    {
        qCritical()<<"Current Date and Time:"<<FileWriteSystem::GetCurrentDataTimeString()<<out_string;
    }
}

void FileWriteSystem::EndWirteLine()
{
    log_file_.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream text_stream(&log_file_);

    text_stream<<"\n";
    log_file_.close();
}

void FileWriteSystem::RemoveLogDay(const QString &log_file_path, const long long day)
{
    QString first_log_line;

    if(FileReadSystem::GetInstance().ReadFileFirstLine(log_file_path,first_log_line))
    {
        QDateTime first_log_time=ExtractLogTime(first_log_line);

        QDateTime current_time=QDateTime::currentDateTime();

        if(first_log_time.daysTo(current_time)>day)
        {
            QFile log_file(log_file_path);
            if(log_file.exists())
            {
                log_file.remove();
                OutMessage(MessageTypeBit::kDebug
                           ,QString("log file deleted due to exceeding: %1 day").arg(QString::number(day)));
            }
        }
    }

}

void FileWriteSystem::RemoveDefaultLogFile()
{
    if(log_file_.exists())
    {
        log_file_.remove();
        OutMessage(MessageTypeBit::kDebug,"Using delete log file");
    }
}

void FileWriteSystem::RemoveLogDay(QFile &log_file, const long long day)
{
    QString first_log_line;

    if(FileReadSystem::GetInstance().ReadFileFirstLine(log_file,first_log_line))
    {
        QDateTime first_log_time=ExtractLogTime(first_log_line);

        QDateTime current_time=QDateTime::currentDateTime();

        // If the time of the obtained log file is longer than the time entered by the user, the entire file is cleared
        if(first_log_time.daysTo(current_time)>=day)
        {
            if(log_file.exists())
            {
                log_file.remove();
                OutMessage(MessageTypeBit::kDebug
                           ,QString("log file deleted due to exceeding: %1 day").arg(QString::number(day)));
            }
        }
    }
}

bool FileWriteSystem::ResetLogFile(QFile &log_file)
{
    if(!log_file.filesystemFileName().empty())
    {
        std::filesystem::path log_file_name=this->log_file_.filesystemFileName();
        this->log_file_.setFileName(log_file.filesystemFileName());

        if(!this->log_file_.exists())
        {
            if(!this->log_file_.open(QIODevice::WriteOnly|QIODevice::Append))
            {
                qWarning() << "Failed to create/open log file.";
                this->log_file_.close();
                this->log_file_.setFileName(log_file_name);
                return false;
            }

            this->log_file_.close();
            return true;
        }
    }

    return false;
}

bool FileWriteSystem::ResetLogFile(const QString &log_file_path)
{
    if(!log_file_path.isEmpty())
    {
        std::filesystem::path log_file_name=this->log_file_.filesystemFileName();
        this->log_file_.setFileName(log_file_path);

        if(!this->log_file_.exists())
        {
            if(!this->log_file_.open(QIODevice::WriteOnly|QIODevice::Append))
            {
                qWarning() << "Failed to create/open log file.";
                this->log_file_.close();
                this->log_file_.setFileName(log_file_name);
                return false;
            }

            this->log_file_.close();
            return true;
        }
    }

    return false;
}

FileWriteSystem &FileWriteSystem::Instance(QString log_file)
{
    static FileWriteSystem instance(log_file);
    return instance;
}

FileWriteSystem::FileWriteSystem(QString log_file):log_file_(QFile()),
    regex_("\"(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})\"")
{
    QString default_log_file=SetDefaultLogFile();
    bool if_file=false;
    if(log_file.isEmpty())
    {
        this->log_file_.setFileName(default_log_file);
    }
    else
    {
        this->log_file_.setFileName(log_file);
    }

    // Check and create log files
    if (!log_file_.exists()) {
        if (!log_file_.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            if_file=true;
            qWarning() << "Failed to create/open log file.";
        }
        log_file_.close();
    }

    // If this file does not exist then a default log file is set.
    if(if_file)
    {
        this->log_file_.setFileName(default_log_file);

        // Check and create log files
        if (!log_file_.exists()) {
            if (!log_file_.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                qWarning() << "Failed to create/open log file.";
            }
            log_file_.close();
        }
    }
}

QString FileWriteSystem::GetCurrentDataTimeString()
{
    QDateTime current_date_time=QDateTime::currentDateTime();
    return current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}

QString FileWriteSystem::SetDefaultLogFile()
{
    QString log_file_path;
    log_file_path=FilePathSystem::GetInstance().GetLogsPath(
        jsontype::JsonType::GetInstance().
        GetJsonData()->GetJsonLogs()->GetLogsPath());
    QString directory_path=QFileInfo(log_file_path).absolutePath();

    QDir directory(directory_path);
    if(!directory.exists())
    {
        if (!directory.mkpath(directory_path))
        {
            qWarning() << "Failed to create log directory.";
        }
    }

    return log_file_path;
}


QDateTime FileWriteSystem::ExtractLogTime(const QString &log_line)
{
    QRegularExpressionMatch match=regex_.match(log_line);
    if(match.hasMatch())
    {
        QString log_time_str=match.captured(1);
        return QDateTime::fromString(log_time_str,"yyyy-MM-dd hh:mm:ss");
    }

    return QDateTime();
}
