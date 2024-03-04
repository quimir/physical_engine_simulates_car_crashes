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

#include "src_include/file_system/json_type/json_button.h"
#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/file_write_system.h"

namespace jsontype
{

jsontype::JsonButton::JsonButton(const QString &path)
{
    if(path.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "Json button path failed!");
        return;
    }

    this->path_=path;
}

QString JsonButton::GetPath() const
{
    return this->path_;
}

bool JsonButton::GetCartoon() const
{
    return this->cartoon_;
}

void JsonButton::SetCartoon(bool cartoon)
{
    if(this->cartoon_==cartoon)
        return;

    this->cartoon_=cartoon;
}

QList<QString> JsonButton::GetButtonMapKeys() const
{
    return this->button_map_.keys();
}

void JsonButton::ParsePathFile()
{
    QJsonObject root_object=FileReadSystem::GetInstance().
                              ReadJsonFileToJsonObject(this->path_);
    ParseJson(root_object);
}

void JsonButton::ParseJson(const QJsonObject &root_object)
{
    QJsonObject root_dir_object=root_object.value("button").toObject();
    for(auto it=root_dir_object.begin();it!=root_dir_object.end();it++)
    {
        QString key=it.key();
        if(key.contains("cartonn",Qt::CaseInsensitive))
        {
            this->cartoon_=root_dir_object[key].toBool();
        }
        else
        {
            QList<JsonButtonKey> button_value=ParseButtonKey(
                key,root_dir_object[key].toObject());
            this->button_map_[key]=button_value;
        }
    }
}

QList<JsonButtonKey> JsonButton::ParseButtonKey(
    const QString &key, const QJsonObject &button_key_object)
{
    QList<JsonButtonKey> button_key;

    for(auto it=button_key_object.begin();it!=button_key_object.end();it++)
    {
        JsonButtonKey button_key_path;
        QString path_key=it.key();
        button_key_path.name=path_key;
        QJsonObject key_path=button_key_object.value(path_key).toObject();

        for(auto button_setting_path=key_path.begin();
             button_setting_path!=key_path.end();button_setting_path++)
        {
            QString button_setting_path_key=button_setting_path.key();
            QJsonValueRef button_setting_path_value=
                button_setting_path.value();

            if(button_setting_path_key=="icon")
            {
                if(!this->cartoon_ && !button_setting_path_value.isNull())
                {
                    if(!button_setting_path_value.toString().isEmpty())
                    {
                        button_key_path.setting["icon"]=
                            button_setting_path_value.toString();
                    }
                    continue;
                }
            }

            else if(button_setting_path_key=="icon_cartonn")
            {
                if(this->cartoon_ && !button_setting_path_value.isNull())
                {
                    if(!button_key_path.setting["icon"].isEmpty()
                        && !button_setting_path_value.toString().isEmpty())
                    {
                        button_key_path.setting["icon"]=
                            button_setting_path_value.toString();
                    }
                }

                else if(!this->cartoon_ &&
                         button_key_path.setting["icon"].isEmpty()
                         && !button_setting_path_value.isNull())
                {
                    if(!button_setting_path_value.toString().isEmpty())
                    {
                        button_key_path.setting["icon"]=
                            button_setting_path_value.toString();
                    }
                }

                else if(button_key_path.setting["icon"].isEmpty())
                {
                    button_key_path.setting["icon"]=
                        key_path.value("icon").toString();
                }

                continue;
            }

            button_key_path.setting[button_setting_path_key]=
                button_setting_path_value.toString();
        }

        button_key.push_back(button_key_path);
    }

    return button_key;
}
}
