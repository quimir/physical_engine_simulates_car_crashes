/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2023 QuiMir <2546670299@qq.com>.
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

#ifndef FILE_SYSTEM_RESOURCES_FILE_TYPE_H
#define FILE_SYSTEM_RESOURCES_FILE_TYPE_H

#include <QString>
#include <QMap>

namespace resourcesfiletype
{
/**
 * @brief The ResourcesType enum Type of resource file, now existing type by json, iamge, shader, style,Obj.
 */
enum class ResourcesType
{
    Image,
    Json,
    GLSL,
    Style,
    Obj
};

class ResourcesTypeToMapper
{
public:
    inline static ResourcesTypeToMapper& GetInstance()
    {
        return Instance();
    }

    inline QString EnumToStringPath(ResourcesType type)const
    {
        return enum_map_.value(type);
    }

    inline QString StringToEnumToStringPath(QString type)const
    {
        QString s(type);
        if(!s.compare("GLSL",Qt::CaseInsensitive))
            return enum_map_.value(ResourcesType::GLSL);
        else if(!s.compare("Image",Qt::CaseInsensitive))
            return enum_map_.value(ResourcesType::Image);
        else if(!s.compare("Style",Qt::CaseInsensitive))
            return enum_map_.value(ResourcesType::Style);
        else if(!s.compare("Obj",Qt::CaseInsensitive))
            return enum_map_.value(ResourcesType::Obj);
        else if(!s.compare("Json",Qt::CaseInsensitive))
            return enum_map_.value(ResourcesType::Json);

        return QString();
    }

    inline QString EnumToString(ResourcesType type)const
    {
        switch(type)
        {
        case ResourcesType::GLSL:
            return "GLSL";
        case ResourcesType::Image:
            return "Image";
        case ResourcesType::Json:
            return "Json";
        case ResourcesType::Style:
            return "Style";
        case ResourcesType::Obj:
            return "Obj";

        default:
            return QString();
        }
    }

private:
    inline static ResourcesTypeToMapper& Instance()
    {
        static ResourcesTypeToMapper instance;
        return instance;
    }

    inline ResourcesTypeToMapper()
    {
        enum_map_[ResourcesType::Image]=":/image/";
        enum_map_[ResourcesType::Json]=":/json/";
        enum_map_[ResourcesType::GLSL]=":/GLSL/";
        enum_map_[ResourcesType::Style]=":/style/";
        enum_map_[ResourcesType::Obj]=":/objs/";
    }

    ResourcesTypeToMapper(const ResourcesTypeToMapper&) = delete;
    ResourcesTypeToMapper& operator=(const ResourcesTypeToMapper&) = delete;

private:
    QMap<ResourcesType,QString> enum_map_;
};
}

#endif // FILE_SYSTEM_RESOURCES_FILE_TYPE_H
