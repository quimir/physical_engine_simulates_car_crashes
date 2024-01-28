/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2024 QuiMir <2546670299@qq.com>.
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

#ifndef FILE_SYSTEM_JSON_DATA_JSON_LOGS_H
#define FILE_SYSTEM_JSON_DATA_JSON_LOGS_H

#include <QString>
#include <QJsonObject>
#include <QDateTime>
#include <QMap>

namespace jsonType
{

class JsonLogs
{
public:
    JsonLogs(const QJsonObject& root_object);

    QVariantMap GetLogProperty()const;

    void SetLogsProperty(QVariantMap new_josn_logs_property);

    QList<QString> GetLogsKeys()const;

    QVariant GetLogsVariant(const QString& key)const;

    qint32 GetLogsDay()const;

    QDateTime GetLogsLastOpenTime()const;

    QString GetLogsPath()const;

    void SetLogsProperty(const QString& key,const QVariant value);

    void ResetLogs(const QJsonObject &root_object);

private:
    void InitJsonLogs(const QJsonObject& root_object);

    void ParseLogs(const QJsonObject& logs_object);

    QVariant GetValue(const QJsonObject& object,const QString& key);

private:
    QJsonObject root_object_;

    QVariantMap log_property_;
};
}

#endif // FILE_SYSTEM_JSON_DATA_JSON_LOGS_H
