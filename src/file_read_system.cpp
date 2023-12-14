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

#include "src_include/file_read_system.h"
#include "src_include/file_wirte_system.h"

QMap<QString,int> FileReadSystem::file_map_=QMap<QString,int>();

FileReadSystem::FileReadSystem()
{

}

QString FileReadSystem::LoadStylesFromFile(const QString &file_name)
{
    QString styles;
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream steam(&file);
    }

    return "";
}

QString FileReadSystem::ReadImageFile(const QString &file_path)
{
    if(file_map_[file_path])
        return file_path;
    QImageReader image_reader(file_path);
    QFile file(file_path);

    if(!file.exists())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,file.fileName()+"failed to open the file. Please check for details"+file.errorString());
        return QString();
    }

    if(!image_reader.format().isEmpty())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Image name: " + image_reader.fileName() +
                                                                ", picture format: " + QString::fromStdString(image_reader.format().toStdString()) +
                                                                ", file width: " + QString::number(image_reader.size().width()) +
                                                                ", height: " + QString::number(image_reader.size().height()));
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"The picture cannot be read because: "+image_reader.errorString());
        return QString();
    }

    file_map_[file_path]++;
    return file_path;
}
