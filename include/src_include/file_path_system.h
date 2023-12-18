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

#ifndef FILE_PATH_SYSTEM_H
#define FILE_PATH_SYSTEM_H

#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

class FilePathSystem
{
public:
    /**
     * @brief GetPath Returns the top-level directory of the project + name
     * @param name File name
     * @return Top-level directory + name of the project
     */
    static QString GetPath(const QString&name);
    static QString GetImagePath(const QString &name);
    static QString GetAttributesSettingPath(const QString &name);
    static QString GetShaderPath(const QString& name);
    static QString GetLogAndDataPath(const QString& name);

private:
    static QString GetRoot();

};

#endif // FILE_PATH_SYSTEM_H
