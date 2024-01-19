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
     * @enum MessageTypeBit enum Nessage type,The temporary types are
     * kDebug, kWarning, kCritical, kFatal, and kInfo.
     * See the Qt manual for details on what these types do.
     */
    enum class MessageTypeBit
    {
        kDebug,
        kWarning,
        kCritical,
        kFatal,
        kInfo
    };

public:
    /**
     * @brief GetInstance The only way to access an object of class
     * FileWriteSystem, no other method can access its object, and the
     * only way to call a function of class FileWriteSystem.
     * @param log_file Log file path, default path when not set.
     * @return Unique object.
     */
    static FileWriteSystem& GetInstance(QString log_file=QString());

    /**
     * @brief CustomMessageHandler Create a handle to get a list of
     * Qt messages, and use a file to store the details of the messages.
     * @param type The type of Qt message.
     * @param context Saves basic information about the file.
     * @param msg File specific messages.
     */
    static void CustomMessageHandler(
    QtMsgType type,
    const QMessageLogContext& context,
    const QString &msg);

    inline QFile& GetLogFile()
    {
        return this->log_file_;
    }

    /**
     * @brief OutMessage Unified log output format. The unified output
     * content is: (Debug|Warning|Critical|Fatal): Current Date and Time
     * (now time) (out message).
     * @param type See MessageTypeBit for details
     * @param out_string Log detail message.
     */
    void OutMessage(FileWriteSystem::MessageTypeBit type,
                    const QString out_string);

    /**
     * @brief EndWirteLineIf the program exits normally, add a endl to the
     * last line of the default log file.
     */
    void EndWirteLine();

    /**
     * @brief RemoveLogDay Check whether the time on the first line of the
     * log file is greater than or equal to the time set by the user to
     * clear the contents of the log file.
     * @param log_file_path Path of the log file.
     * @param day User specifies the number of days to clear logs.
     */
    void RemoveLogDay(const QString &log_file_path,const long long day);

    /**
     * @brief RemoveDefaultLogFile Remove all information from the default
     * logfile.
     */
    void RemoveDefaultLogFile();

    /**
     * @brief RemoveLogDay Check whether the time on the first line of the
     * log file is greater than or equal to the time set by the user to
     * clear the contents of the log file.
     * @param log_file Log files that need to be removed. If not,
     * it is the default log file.
     * @param day User specifies the number of days to clear logs.
     */
    void RemoveLogDay(QFile &log_file, const long long day);

    /**
     * @brief ResetLogFileThe RESET log file is set according to the name of
     * the log file passed in. If the file does not exist with respect to the
     * system, the default log file will be re-invoked.
     * @param log_file The reset log file.
     * @return Returns true if the reset was successful, false otherwise.
     */
    bool ResetLogFile(QFile& log_file);

    /**
     * @brief ResetLogFileResets the logfile. The file is set according to
     * the path of the logfile passed in. If not, the default logfile is
     * invoked again.
     * @param log_file_path Log file path that needs to be reset.
     * @return Returns true if the reset was successful, false otherwise.
     */
    bool ResetLogFile(const QString& log_file_path);

private:
    /**
     * @brief Instance Gets the unique object of the FileWriteSystem
     * @param log_file Log file path, default path when not set.
     * @return Unique object.
     */
    static FileWriteSystem& Instance(QString log_file=QString());

    /**
     * @brief FileWriteSystem Initialize the basic data of the class,
     * allowing to set its own log file path.
     * @param log_file Log file path, default path when not set.
     */
    FileWriteSystem(QString log_file=QString());

    /**
     * @brief GetCurrentDataTimeString Gets the normalized time format
     * @return Normalized time string
     */
    QString GetCurrentDataTimeString();

    /**
     * @brief SetDefaultLogFile Set the default logfile, usually located
     * in the /logs/ directory, the default directory file name is log_file.
     * log can be reset by ResetLogFile.The /logs/ directory is created
     * automatically if it doesn't exist in the project.
     * @return Path to the log file.
     */
    QString SetDefaultLogFile();

    /**
     * @brief ReadFirstLogLine Gets the first line of the log file
     * (if it exists) and reads it to the first_line.
     * @param log_file log file.
     * @param first_line Information about the first line of a log file.
     * @return Return true on success.
     */
    bool ReadFirstLogLine(QFile &log_file,QString &first_line);

    /**
     * @brief ExtractLogTime Obtain the time of the first line in the log
     * file using a regular expression.
     * @param log_line The first line in the log file.
     * @return If yes, the time data in the format yyyy-MM-dd hh:mm:ss is
     * returned. Otherwise, Null is returned.
     */
    QDateTime ExtractLogTime(const QString &log_line);

private:
    // Default location where logs are saved.
    QFile log_file_;

    /* The output format is: (Debug|Warning|Critical|Fatal):Current Date
     * and Time (now time) (out message).*/
    QRegularExpression regex_;
};

#endif // FILE_SYSTEM_FILE_WIRTE_SYSTEM_H
