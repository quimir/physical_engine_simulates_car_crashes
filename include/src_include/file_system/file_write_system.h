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

#ifndef FILE_SYSTEM_FILE_WIRTE_SYSTEM_H
#define FILE_SYSTEM_FILE_WIRTE_SYSTEM_H

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <qlogging.h>
#include <QString>
#include <QRegularExpression>
#include <QFileInfo>

class FileWriteSystem
{
public:
    /**
     * @brief The MessageTypeBit enum Nessage type
     */
    enum class MessageTypeBit
    {
        Debug,
        Warning,
        Critical,
        Fatal,
        Info
    };

public:
    static FileWriteSystem& GetInstance();

    /**
     * @brief CustomMessageHandler Create a handle to get a list of Qt messages, and use a file to store the details of the messages.
     * @param type The type of Qt message.
     * @param context Saves basic information about the file.
     * @param msg File specific messages.
     */
    static void CustomMessageHandler(QtMsgType type,const QMessageLogContext& context,const QString &msg);

    inline QFile& GetLogFile()
    {
        return this->log_file_;
    }

    /**
     * @brief OutMessage Unified log output format. The unified output content is: (Debug|Warning|Critical|Fatal): Current Date and Time (now time) (out message).
     * @param type See MessageTypeBit for details
     * @param out_string Log detail message.
     */
    void OutMessage(FileWriteSystem::MessageTypeBit type,const QString out_string);

    /**
     * @brief EndWirteLineIf the program exits normally, add a endl to the last line of the default log file.
     */
    void EndWirteLine();

    /**
     * @brief DeleteLogDay Check whether the time on the first line of the log file is greater than or equal to the time set by the user to clear the contents of the log file.
     * @param log_file_path Path of the log file.
     * @param day User specifies the number of days to clear logs.
     */
    void DeleteLogDay(const QString &log_file_path,const long long day);

    void DeleteLogFile();

    void DeleteLogDay(QFile &log_file, const long long day);

private:
    static FileWriteSystem& Instance();

    FileWriteSystem();

    QString GetCurrentDataTimeString();

    bool ReadFirstLogLine(const QString &file_path,QString &first_line);

    /**
     * @brief ReadFirstLogLine Gets the first line of the log file (if it exists) and reads it to the first_line.
     * @param log_file log file.
     * @param first_line Information about the first line of a log file.
     * @return Return true on success.
     */
    bool ReadFirstLogLine(QFile &log_file,QString &first_line);

    /**
     * @brief ExtractLogTime Obtain the time of the first line in the log file using a regular expression.
     * @param log_line The first line in the log file.
     * @return If yes, the time data in the format yyyy-MM-dd hh:mm:ss is returned. Otherwise, Null is returned.
     */
    QDateTime ExtractLogTime(const QString &log_line);

private:
    // Default location where logs are saved.
    QFile log_file_;
    // The output format is: (Debug|Warning|Critical|Fatal): Current Date and Time (now time) (out message).
    QRegularExpression regex_;

};

#endif // FILE_SYSTEM_FILE_WIRTE_SYSTEM_H
