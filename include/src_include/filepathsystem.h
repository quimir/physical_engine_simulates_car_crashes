/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       filepathsystem.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/


#ifndef FILEPATHSYSTEM_H
#define FILEPATHSYSTEM_H

#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

class FilePathSystem
{
public:
    static QString GetPath(const QString&path);
    static QString GetImagePath(const QString &path);
    static QString GetAttributesSettingPath(const QString &path);
    static QString GetShaderPath(const QString& path);

private:
    static QString GetRoot();

};

#endif // FILEPATHSYSTEM_H
