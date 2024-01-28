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

#include "src_include/file_system/json_type/json_data/json_logs.h"
#include "src_include/file_system/file_write_system.h"

namespace jsonType
{

JsonLogs::JsonLogs(const QJsonObject &root_object)
{
    InitJsonLogs(root_object);
}

QVariantMap JsonLogs::GetLogProperty() const
{
    return this->log_property_;
}

void JsonLogs::SetLogsProperty(QVariantMap new_josn_logs_property)
{
    this->log_property_=new_josn_logs_property;
}

QList<QString> JsonLogs::GetLogsKeys() const
{
    return this->log_property_.keys();
}

QVariant JsonLogs::GetLogsVariant(const QString &key) const
{
    return this->log_property_[key];
}

qint32 JsonLogs::GetLogsDay() const
{
    return this->log_property_["log"].toInt();
}

QDateTime JsonLogs::GetLogsLastOpenTime() const
{
    return this->log_property_["last_open_time"].toDateTime();
}

QString JsonLogs::GetLogsPath() const
{
    return this->log_property_["path"].toString();
}

void JsonLogs::SetLogsProperty(const QString &key, const QVariant value)
{
    this->log_property_[key]=value;
}


void JsonLogs::ResetLogs(const QJsonObject &root_object)
{
    InitJsonLogs(root_object);
}

void JsonLogs::InitJsonLogs(const QJsonObject &root_object)
{
    if(root_object.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "No json logs object!");
        return;
    }

    this->root_object_=root_object;
    ParseLogs(this->root_object_);
}

void JsonLogs::ParseLogs(const QJsonObject &logs_object)
{
    for(auto it=logs_object.constBegin();it!=logs_object.constEnd();it++)
    {
        this->log_property_.insert(it.key(),it.value().toVariant());
    }
}

}
