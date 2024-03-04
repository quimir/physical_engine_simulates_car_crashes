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

#ifndef FILE_SYSTEM_JSON_DATA_JSONDATA_H
#define FILE_SYSTEM_JSON_DATA_JSONDATA_H

#include "json_GLSL.h"
#include "json_logs.h"
#include "json_model.h"
#include "json_image.h"
#include "src_include/file_system/resources_file_type.h"

namespace jsontype
{
class JsonData
{
public:
    JsonData(const QString path);

    JsonGLSL* GetJsonGLSL();

    JsonLogs* GetJsonLogs();

    JsonModel* GetJsonModel();

    JsonImage* GetJsonImage();

    void PrasePathFile();

    void ResetJsonData(const QString path);

    qint32 SavingTheJsonFile();

    ~JsonData();

private:
    void InitValues(QString key,QJsonObject& json_object);

    void SetInitalValues(resourcesfiletype::ResourcesType type,QJsonObject json_object);

private:
    bool IsReset;

    QString path_;

    /* Json data */
    JsonGLSL* json_glsl_;
    JsonLogs* json_logs_;
    JsonModel* json_model_;
    JsonImage* json_image_;
};
}

#endif // FILE_SYSTEM_JSON_DATA_JSONDATA_H
