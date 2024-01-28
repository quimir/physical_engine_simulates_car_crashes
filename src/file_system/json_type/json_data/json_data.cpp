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

#include "src_include/file_system/json_type/json_data/json_data.h"
#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/file_write_system.h"

namespace jsonType
{

JsonData::JsonData(const QString path)
{
    if(path.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "Json data file path error!");
        return;
    }

    this->path_=path;
}

JsonGLSL *JsonData::GetJsonGLSL()
{
    if(this->json_glsl_)
        return this->json_glsl_;

    return nullptr;
}

JsonLogs *JsonData::GetJsonLogs()
{
    if(this->json_logs_)
        return this->json_logs_;

    return nullptr;
}

JsonModel *JsonData::GetJsonModel()
{
    if(this->json_model_)
        return this->json_model_;

    return nullptr;
}

JsonImage *JsonData::GetJsonImage()
{
    if(this->json_image_)
        return this->json_image_;

    return nullptr;
}

void JsonData::PrasePathFile()
{
    QJsonObject json_object=FileReadSystem::GetInstance().ReadJsonFileToJsonObject(
        this->path_);

    for(auto it=json_object.begin();it!=json_object.end();it++)
    {
        QString key=it.key();
        InitValues(key,json_object[key].toObject());
    }
}

JsonData::~JsonData()
{
    if(this->json_glsl_)
        delete json_glsl_;
    if(this->json_image_)
        delete json_image_;
    if(this->json_logs_)
        delete json_logs_;
    if(this->json_model_)
        delete json_model_;
}

void JsonData::InitValues(QString key, QJsonObject json_object)
{
    if(!key.isEmpty())
    {
        if(!key.contains("logs",Qt::CaseInsensitive))
        {
            if(nullptr==this->json_logs_)
            {
                this->json_logs_=new JsonLogs(json_object);
            }
            else
            {
                this->json_logs_->ResetLogs(json_object);
            }
        }
        else
        {
            SetInitalValues(
                resourcesfiletype::ResourcesTypeToMapper::GetInstance().StringToEnum(key),
                json_object);
        }
    }
}

void JsonData::SetInitalValues(resourcesfiletype::ResourcesType type, QJsonObject json_object)
{
    switch (type)
    {
    case resourcesfiletype::ResourcesType::kImages:
    {
        if(nullptr==this->json_image_)
        {
            this->json_image_=new JsonImage(json_object);
        }
        else
        {
            this->json_image_->ResetJsonImage(json_object);
        }
    }
    break;
    case resourcesfiletype::ResourcesType::kGLSL:
    {
        if(nullptr==this->json_glsl_)
        {
            this->json_glsl_=new JsonGLSL(json_object);
        }
        else
        {
            this->json_glsl_->ResetJsonGLSL(json_object);
        }
    }
    break;
    case resourcesfiletype::ResourcesType::kModel:
    {
        if(nullptr==this->json_model_)
        {
            this->json_model_=new JsonModel(json_object);
        }
        else
        {
            this->json_model_->ResetJsonModel(json_object);
        }
    }
    break;
    case resourcesfiletype::ResourcesType::kTextures:
        break;
    default:
        break;
    }
}

}
