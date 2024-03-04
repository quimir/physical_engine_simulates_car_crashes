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

#include "src_include/file_system/json_type/json_type.h"
#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/file_path_system.h"

namespace jsontype
{
JsonType &JsonType::GetInstance(const QString &json_file_index_path)
{
    return Instance(json_file_index_path);
}

JsonType::~JsonType()
{
    if(this->json_basic_setting_)
    {
        delete this->json_basic_setting_;
    }

    if(this->json_button_)
    {
        delete this->json_button_;
    }

    if(this->json_data_)
    {
        delete this->json_data_;
    }

    if(this->json_environment_setting)
    {
        delete this->json_environment_setting;
    }

    if(this->json_more_setting_)
    {
        delete this->json_more_setting_;
    }
}

void JsonType::ParseJsonObject(const QJsonObject &json_object)
{
    for(auto it=json_object.begin();it!=json_object.end();it++)
    {
        QString key=it.key();
        if(key.contains("data",Qt::CaseInsensitive))
        {
            this->json_data_=new JsonData(
                FilePathSystem::GetInstance().GetResourcesPath(
                    resourcesfiletype::ResourcesType::kJson,json_object[key].toString()));
            this->json_data_->PrasePathFile();
        }
        else if(key.contains("basic_setting",Qt::CaseInsensitive))
        {
            this->json_basic_setting_=new JsonBasicSetting();
        }
        else if(key.contains("button",Qt::CaseInsensitive))
        {
            this->json_button_=new JsonButton(
                FilePathSystem::GetInstance().GetResourcesPath(
                    resourcesfiletype::ResourcesType::kJson,json_object[key].toString()));
            this->json_button_->ParsePathFile();
        }
        else if(key.contains("more_setting",Qt::CaseInsensitive))
        {
            this->json_more_setting_=new JsonMoreSetting();
        }
        else if(key.contains("environment_setting",Qt::CaseInsensitive))
        {
            this->json_environment_setting=new JsonEnvironmentSetting();
        }
    }
}

JsonType &JsonType::Instance(const QString &json_file_index_path)
{
    static JsonType instance(json_file_index_path);
    return instance;
}

JsonType::JsonType(const QString &json_file_index_path)
{
    if(json_file_index_path.isEmpty())
    {
        emit ResourceLoadingError();
        return;
    }

    QJsonObject json_object=FileReadSystem::GetInstance().ReadJsonFileToJsonObject(json_file_index_path);

    this->path_=json_file_index_path;

    ParseJsonObject(json_object);
}

JsonEnvironmentSetting *JsonType::GetJsonEnvironmentSetting() const
{
    return json_environment_setting;
}

JsonMoreSetting *JsonType::GetJsonMoreSetting() const
{
    return json_more_setting_;
}

JsonButton *JsonType::GetJsonButton() const
{
    return json_button_;
}

JsonBasicSetting *JsonType::GetJsonBasicSetting() const
{
    return json_basic_setting_;
}

JsonData *JsonType::GetJsonData() const
{
    return json_data_;
}

}
