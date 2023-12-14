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
 * @file       file_read_system.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef FILE_READ_SYSTEM_H
#define FILE_READ_SYSTEM_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QImageReader>
#include <QMap>

class FileReadSystem
{
public:
    FileReadSystem();

    static QString LoadStylesFromFile(const QString&file_name);

    static QString ReadImageFile(const QString& file_path);

private:
    static QMap<QString,int> file_map_;
};

#endif // FILE_READ_SYSTEM_H