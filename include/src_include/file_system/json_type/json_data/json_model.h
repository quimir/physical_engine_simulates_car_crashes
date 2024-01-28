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

#ifndef FILE_SYSTEM_JSON_DATA_JSON_MODEL_H
#define FILE_SYSTEM_JSON_DATA_JSON_MODEL_H

#include <QMap>
#include <QString>
#include <QJsonObject>

namespace jsonType
{
class JsonModel
{
public:
    JsonModel(const QJsonObject& root_object);

    QList<QString> GetModelMapKeys()const;

    QString GetModelMapValue(const QString &key)const;

    void ResetJsonModel(const QJsonObject& root_object);

private:
    void InitJsonModel(const QJsonObject& root_object);

    void ParseModels(const QJsonObject& model_object);

private:
    QJsonObject root_object_;

    QMap<QString,QString> model_map_;
};
}

#endif // FILE_SYSTEM_JSON_DATA_JSON_MODEL_H
