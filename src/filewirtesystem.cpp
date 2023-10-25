#include "src_include/filewirtesystem.h"

void FileWirteSystem::CustomMessageHandler(QtMsgType type,const QMessageLogContext& context,const QString &msg)
{
    QFile log_file("../data_and_log/log_file.log");
    log_file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream text_stream(&log_file);

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

    log_file.close();
}

void FileWirteSystem::OutMessage(const int type, const QString out_string)
{
    if(type==static_cast<int>(MessageType::debug))
    {
        qDebug()<<"Current Date and Time:"<<FileWirteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type==static_cast<int>(MessageType::warning))
    {
        qWarning()<<"Current Date and Time:"<<FileWirteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type==static_cast<int>(MessageType::critical))
    {
        qCritical()<<"Current Date and Time:"<<FileWirteSystem::GetCurrentDataTimeString()<<out_string;
    }
}

void FileWirteSystem::OutMessage(const QString type,const QString out_string)
{
    if(type=="debug"||type=="Debug")
    {
        qDebug()<<"Current Date and Time:"<<FileWirteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type=="warning"||type=="Warning")
    {
        qWarning()<<"Current Date and Time:"<<FileWirteSystem::GetCurrentDataTimeString()<<out_string;
    }
    else if(type=="critical"||type=="Critical")
    {
        qCritical()<<"Current Date and Time:"<<FileWirteSystem::GetCurrentDataTimeString()<<out_string;
    }
}

void FileWirteSystem::EndWirteLine()
{
    QFile log_file("../data_and_log/log_file.log");
    log_file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream text_stream(&log_file);

    text_stream<<"\n";
    log_file.close();
}

void FileWirteSystem::DeleteLogDay(const QString &file_path, const long long day)
{
    QFile log_file(file_path);

    if(!log_file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        FileWirteSystem::OutMessage(1,QString("Failed to open file name: %1").arg(file_path));
        return;
    }

    QFileInfo log_file_info(log_file);

    QDateTime last_modified=log_file_info.lastModified();

    QDateTime current_time=QDateTime::currentDateTime();

    if(last_modified.daysTo(current_time)>day)
    {
        if(log_file.exists())
        {
            log_file.remove();
            FileWirteSystem::OutMessage(1,QString("Log file deleted due to exceeding: %1").arg(QString::number(day)));
        }
    }
}

void FileWirteSystem::DeleteLogDay(QFile log_file, const long long day)
{

    if(!log_file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        FileWirteSystem::OutMessage(1,QString("Failed to open file"));
        return;
    }

    QFileInfo log_file_info(log_file);

    QDateTime last_modified=log_file_info.lastModified();

    QDateTime current_time=QDateTime::currentDateTime();

    if(last_modified.daysTo(current_time)>day)
    {
        if(log_file.exists())
        {
            log_file.remove();
            FileWirteSystem::OutMessage(1,QString("Log file deleted due to exceeding: %1").arg(QString::number(day)));
        }
    }

}

void FileWirteSystem::DeleteLogDay(const long long day)
{
    QFile log_file("../data_and_log/log_file.log");

    if(!log_file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        FileWirteSystem::OutMessage(1,QString("Failed to open file"));
        return;
    }

    QFileInfo log_file_info(log_file);

    QDateTime last_modified=log_file_info.lastModified();

    QDateTime current_time=QDateTime::currentDateTime();

    if(last_modified.daysTo(current_time)>day)
    {
        if(log_file.exists())
        {
            log_file.remove();
            FileWirteSystem::OutMessage(1,QString("Log file deleted due to exceeding: %1").arg(QString::number(day)));
        }
    }
}

QString FileWirteSystem::GetCurrentDataTimeString()
{
    QDateTime current_date_time=QDateTime::currentDateTime();
    return current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}
