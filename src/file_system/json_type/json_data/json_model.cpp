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

#include "src_include/file_system/json_type/json_data/json_model.h"
#include "src_include/file_system/file_write_system.h"

namespace jsontype
{
JsonModel::JsonModel(const QJsonObject &root_object)
{
    InitJsonModel(root_object);
}

QList<QString> JsonModel::GetModelMapKeys() const
{
    return this->model_map_.keys();
}

QString JsonModel::GetModelMapValue(const QString& key) const
{
    return this->model_map_.value(key);
}

void JsonModel::ResetJsonModel(const QJsonObject &root_object)
{
    InitJsonModel(root_object);
}

QJsonObject JsonModel::GetRootObject() const
{
    return this->root_object_;
}

void JsonModel::InitJsonModel(const QJsonObject &root_object)
{
    if(root_object.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "No json logs object!");
        return;
    }

    this->root_object_=root_object;
    ParseModels(root_object);
}

void JsonModel::ParseModels(const QJsonObject &model_object)
{
    for(auto it=model_object.constBegin();it!=model_object.constEnd();it++)
    {
        QString model_name=it.key();
        QString model_path=it.value().toString();

        this->model_map_[model_name]=model_path;
    }
}
}
