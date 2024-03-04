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

#include "src_include/file_system/json_type/json_data/json_GLSL.h"
#include "qjsonarray.h"
#include "src_include/file_system/file_write_system.h"

namespace jsontype
{

JsonGLSL::JsonGLSL(const QJsonObject &root_object)
{
    InitJsonGLSL(root_object);
}

QMap<QString, JsonGLSLProperty> JsonGLSL::GetGLSLMap() const
{
    return this->glsl_map_;
}

JsonGLSLProperty JsonGLSL::GetGLSLProperty(QString key) const
{
    return this->glsl_map_[key];
}

void JsonGLSL::ResetJsonGLSL(const QJsonObject &root_object)
{
    InitJsonGLSL(root_object);
}

QJsonObject JsonGLSL::GetRootObject() const
{
    return this->root_object_;
}

void JsonGLSL::InitJsonGLSL(const QJsonObject &root_object)
{
    if(root_object.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                  "Json GLSL no object!");
        return;
    }

    this->root_object_=root_object;
    ParseGLSL(this->root_object_);
}


JsonGLSLProperty JsonGLSL::ParseGLSLProperty(const QJsonObject &property_object)
{
    JsonGLSLProperty property;

    for(auto path_it=property_object.begin();path_it!=property_object.end();path_it++)
    {
        QList<QString> path;
        if(path_it.value().isArray())
        {
            QJsonArray path_array=path_it.value().toArray();
            for(qint32 i=0;i<path_array.size();i++)
            {
                if(path_array[i].isArray())
                {
                    path.push_back(path_array[i].toString());
                }
                else if(path_array[i].isString())
                {
                    if(!path_array[i].toString().isEmpty())
                    {
                        path.push_back(path_array[i].toString());
                    }
                }
            }
        }
        if(!path.isEmpty())
        {
            property.shader_map[path_it.key()]=path;
        }
    }

    return property;
}

void JsonGLSL::ParseGLSL(const QJsonObject &glsl_object)
{
    for(auto it=glsl_object.begin();it!=glsl_object.end();it++)
    {
        if(it.value().isObject())
        {
            JsonGLSLProperty property=ParseGLSLProperty(it.value().toObject());
            this->glsl_map_[it.key()]=property;
        }
    }
}

}
