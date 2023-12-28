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

FileWriteSystem &FileWriteSystem::GetInstance()
{
    return Instance();
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
    if(type==MessageTypeBit::Debug)
    {
        qDebug()<<"Current Date and Time:"<<FileWriteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type==MessageTypeBit::Warning)
    {
        qWarning()<<"Current Date and Time:"<<FileWriteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type==MessageTypeBit::Critical)
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

void FileWriteSystem::DeleteLogDay(const QString &log_file_path, const long long day)
{
    QString first_log_line;

    if(ReadFirstLogLine(log_file_path,first_log_line))
    {
        QDateTime first_log_time=ExtractLogTime(first_log_line);

        QDateTime current_time=QDateTime::currentDateTime();

        if(first_log_time.daysTo(current_time)>day)
        {
            QFile log_file(log_file_path);
            if(log_file.exists())
            {
                log_file.remove();
                OutMessage(MessageTypeBit::Debug,QString("log file deleted due to exceeding: %1 day").arg(QString::number(day)));
            }
        }
    }

}

void FileWriteSystem::DeleteLogFile()
{
    if(log_file_.exists())
    {
        log_file_.remove();
        OutMessage(MessageTypeBit::Debug,"Using delete log file");
    }
}

void FileWriteSystem::DeleteLogDay(QFile &log_file, const long long day)
{
    QString first_log_line;

    if(ReadFirstLogLine(log_file,first_log_line))
    {
        QDateTime first_log_time=ExtractLogTime(first_log_line);

        QDateTime current_time=QDateTime::currentDateTime();

        // If the time of the obtained log file is longer than the time entered by the user, the entire file is cleared
        if(first_log_time.daysTo(current_time)>=day)
        {
            if(log_file.exists())
            {
                log_file.remove();
                OutMessage(MessageTypeBit::Debug,QString("log file deleted due to exceeding: %1 day").arg(QString::number(day)));
            }
        }
    }
}

FileWriteSystem &FileWriteSystem::Instance()
{
    static FileWriteSystem instance;
    return instance;
}

FileWriteSystem::FileWriteSystem():log_file_(QFile()),regex_("\"(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})\"")
{
    QString file_path=FilePathSystem::GetInstance().GetLogsPath("log_file.log");
    QString directory_path=QFileInfo(file_path).absolutePath();

    // Check and create a log folder
    QDir directory(directory_path);
    if(!directory.exists())
    {
        if (!directory.mkpath(directory_path))
        {
            qWarning() << "Failed to create log directory.";
        }
    }

    log_file_.setFileName(file_path);

    // Check and create log files
    if (!log_file_.exists()) {
        if (!log_file_.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            qWarning() << "Failed to create/open log file.";
        }
        log_file_.close();
    }
}

QString FileWriteSystem::GetCurrentDataTimeString()
{
    QDateTime current_date_time=QDateTime::currentDateTime();
    return current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}

bool FileWriteSystem::ReadFirstLogLine(const QString &file_path, QString &first_line)
{
    QFile file(file_path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        if(!in.atEnd())
        {
            first_line=in.readLine();
            file.close();
            return true;
        }
        file.close();
    }
    return false;
}

bool FileWriteSystem::ReadFirstLogLine(QFile &log_file, QString &first_line)
{
    if(log_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&log_file);
        if(!in.atEnd())
        {
            first_line=in.readLine();
            log_file.close();
            return true;
        }
        log_file.close();
    }
    return false;
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
