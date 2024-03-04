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

#ifndef FILE_SYSTEM_JSON_DATA_JSON_GLSL_H
#define FILE_SYSTEM_JSON_DATA_JSON_GLSL_H

#include <QString>
#include <QList>
#include <QMap>
#include <QJsonObject>

namespace jsontype
{
struct JsonGLSLProperty
{
    QMap<QString,QList<QString>> shader_map;
};

class JsonGLSL
{
public:
    JsonGLSL(const QJsonObject& root_object);

    QMap<QString,JsonGLSLProperty> GetGLSLMap()const;

    JsonGLSLProperty GetGLSLProperty(QString key)const;

    void SetGLSLMap(QString key,QList<QString> path);

    void ResetJsonGLSL(const QJsonObject& root_object);

    QJsonObject GetRootObject()const;

private:
    void InitJsonGLSL(const QJsonObject& root_object);

    void ParseGLSL(const QJsonObject& glsl_object);

    JsonGLSLProperty ParseGLSLProperty(const QJsonObject& property_object);

private:
    QJsonObject root_object_;

    QMap<QString,JsonGLSLProperty> glsl_map_;
};
}

#endif // FILE_SYSTEM_JSON_DATA_JSON_GLSL_H
