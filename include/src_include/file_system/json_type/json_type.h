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

#ifndef FILE_SYSTEM_JSONTYPE_H
#define FILE_SYSTEM_JSONTYPE_H

#include "json_data/json_data.h"
#include "json_basic_setting.h"
#include "json_button.h"
#include "json_more_setting.h"
#include "json_environment_setting.h"
#include <QObject>

namespace jsontype
{
class JsonType : public QObject
{
    Q_OBJECT
public:
    static JsonType& GetInstance(const QString& json_file_index_path=QString());

    ~JsonType();

    JsonData* GetJsonData() const;

    JsonBasicSetting* GetJsonBasicSetting() const;

    JsonButton* GetJsonButton() const;

    JsonMoreSetting* GetJsonMoreSetting() const;

    JsonEnvironmentSetting* GetJsonEnvironmentSetting() const;

private:
    void ParseJsonObject(const QJsonObject& json_object);

    static JsonType& Instance(const QString& json_file_index_path);

    JsonType(const QString& json_file_index_path);

signals:
    void ResourceLoadingError();

private:
    QString path_;

    JsonData* json_data_;
    JsonBasicSetting* json_basic_setting_;
    JsonButton* json_button_;
    JsonMoreSetting* json_more_setting_;
    JsonEnvironmentSetting* json_environment_setting;
};
}

#endif // FILE_SYSTEM_JSONTYPE_H
