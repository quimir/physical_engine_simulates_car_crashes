/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       file_wirte_system.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef FILE_WIRTE_SYSTEM_H
#define FILE_WIRTE_SYSTEM_H

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
    /**
     * @brief The MessageTypeBit enum Nessage type
     */
    enum MessageTypeBit
    {
        Debug=0x0001,
        Warning=0x0002,
        Critical=0x0003,
        Fatal=0x0004,
        Info=0x0005
    };

public:
    FileWirteSystem()=delete;

    /**
     * @brief CustomMessageHandler Create a handle to get a list of Qt messages, and use a file to store the details of the messages.
     * @param type The type of Qt message.
     * @param context Saves basic information about the file.
     * @param msg File specific messages.
     */
    static void CustomMessageHandler(QtMsgType type,const QMessageLogContext& context,const QString &msg);

    /**
     * @brief OutMessage Unified log output format. The unified output content is: (Debug|Warning|Critical|Fatal): Current Date and Time (now time) (out message).
     * @param type See MessageTypeBit for details
     * @param out_string Log detail message.
     */
    static void OutMessage(FileWirteSystem::MessageTypeBit type,const QString out_string);

    /**
     * @brief EndWirteLineIf the program exits normally, add a endl to the last line of the default log file.
     */
    static void EndWirteLine();

    /**
     * @brief DeleteLogDay Check whether the time on the first line of the log file is greater than or equal to the time set by the user to clear the contents of the log file.
     * @param log_file_path Path of the log file.
     * @param day User specifies the number of days to clear logs.
     */
    static void DeleteLogDay(const QString &log_file_path,const long long day);

    static void DeleteLogFile();

    static void DeleteLogDay(QFile &log_file, const long long day);

private:

    static QString GetCurrentDataTimeString();

    static bool ReadFirstLogLine(const QString &file_path,QString &first_line);

    /**
     * @brief ReadFirstLogLine Gets the first line of the log file (if it exists) and reads it to the first_line.
     * @param log_file log file.
     * @param first_line Information about the first line of a log file.
     * @return Return true on success.
     */
    static bool ReadFirstLogLine(QFile &log_file,QString &first_line);

    /**
     * @brief ExtractLogTime Obtain the time of the first line in the log file using a regular expression.
     * @param log_line The first line in the log file.
     * @return If yes, the time data in the format yyyy-MM-dd hh:mm:ss is returned. Otherwise, Null is returned.
     */
    static QDateTime ExtractLogTime(const QString &log_line);

public:
    // Default location where logs are saved.
    static QFile log_file_;

private:
    // The output format is: (Debug|Warning|Critical|Fatal): Current Date and Time (now time) (out message).
    static QRegularExpression regex;

};

#endif // FILE_WIRTE_SYSTEM_H
