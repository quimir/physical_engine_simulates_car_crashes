/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       filewirtesystem.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/26
 * @history
 *****************************************************************************/

#ifndef FILEWIRTESYSTEM_H
#define FILEWIRTESYSTEM_H

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <qlogging.h>
#include <QString>
#include <QRegularExpression>
#include <QFileInfo>

class FileWirteSystem
{
public:
    FileWirteSystem()=delete;

    /**
     * @brief CustomMessageHandler Create a handle to get a list of Qt messages, and create a file to store the details of the messages
     * @param type The type of Qt message
     * @param context Saves basic information about the file
     * @param msg File specific messages
     */
    static void CustomMessageHandler(QtMsgType type,const QMessageLogContext& context,const QString &msg);

    /**
     * @brief OutMessage Normalized Qt output information
     * @param type See the MessageType enum for details
     * @param out_string A detailed description of the message
     */
    static void OutMessage(const int type,const QString out_string);

    static void OutMessage(const QString type,const QString out_string);

    static void EndWirteLine();

    static void DeleteLogDay(const QString &log_file_path,const long long day);

    static void DeleteLogDay(QFile &log_file, const long long day);

    static QFile log_file_;

private:
    enum class MessageType
    {
        debug=1,
        warning,
        critical,
        fatal,
        info
    };

    static QString GetCurrentDataTimeString();

    static bool ReadFirstLogLine(const QString &file_path,QString &first_line);

    static bool ReadFirstLogLine(QFile &log_file,QString &first_line);

    static QDateTime ExtractLogTime(const QString &log_line);

    static QRegularExpression regex;

};

#endif // FILEWIRTESYSTEM_H
