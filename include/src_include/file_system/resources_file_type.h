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
 * @enum The ResourcesType enum Type of resource file, now existing type by json, iamge, shader, style,Obj.
 */
enum class ResourcesType
{
    kImage,
    kJson,
    GLSL,
    kStyle,
    kObj,
    kModel,
    kNone // error
};

class ResourcesTypeToMapper
{
public:
    /**
     * @brief GetInstance The only way to access an object of class ResourcesTypeToMapper,
     *  no other method can access its object, and the only way to call a function of class ResourcesTypeToMapper.
     * @return Unique object.
     */
    static ResourcesTypeToMapper& GetInstance();

    /**
     * @brief EnumToStringPath Relative path translation from ResourcesTypes types to RCC
     * @param type RCC existing types
     * @return The relative path of type to RCC
     */
    QString EnumToStringPath(ResourcesType type)const;

    /**
     * @brief StringToEnumToStringPath Look for a name that matches the RCC resource file (regardless of case rules)
     * , and if it matches, return the relative path to the RCC for that type.
     * @param type A string to evaluate
     * @return The relative path of the type in RCC
     */
    QString StringToEnumToStringPath(QString type)const;

    /**
     * @brief EnumToString Converts a fixed type from the ResourcesTypes type to a string
     * @param type target type
     * @return Converted string
     */
    QString EnumToString(ResourcesType type)const;

    ResourcesType StringToEnum(QString type)const;

private:
    /**
     * @brief Instance Gets the unique object of the ResourcesTypeToMapper.
     * @return Unique object.
     */
    static ResourcesTypeToMapper& Instance();

    /**
     * @brief ResourcesTypeToMapper Initialize the basic data of the class.
     */
    ResourcesTypeToMapper();

    ResourcesTypeToMapper(const ResourcesTypeToMapper&) = delete;
    ResourcesTypeToMapper& operator=(const ResourcesTypeToMapper&) = delete;

private:
    QMap<ResourcesType,QString> enum_map_;
};
}

#endif // FILE_SYSTEM_RESOURCES_FILE_TYPE_H
