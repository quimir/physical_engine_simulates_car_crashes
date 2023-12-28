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

#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/file_wirte_system.h"
#include "src_include/file_system/file_path_system.h"
#include <QJsonArray>
#include <QJsonDocument>

QSet<QString> FileReadSystem::file_map_=QSet<QString>();

QString FileReadSystem::LoadStylesFromFile(const QString &file_name)
{
    return QString();
}

QString FileReadSystem::ReadImageFile(const QString &file_path)
{
    if(file_map_.contains(file_path)||file_path.isEmpty())
    {
        return file_path;
    }

    QImageReader image_reader(file_path);
    QFile file(file_path);

    if(!file.exists())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,file.fileName()+"failed to open the file. Please check for details"+file.errorString());
        return file_path;
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
        return file_path;
    }

    file_map_.insert(file_path);
    return file_path;
}

QFile &FileReadSystem::ReadImageFile(QFile &image_file)
{
    if(file_map_.contains(image_file.fileName())||image_file.fileName().isEmpty())
    {
        return image_file;
    }

    if(!image_file.exists())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,image_file.fileName()+"failed to open the file. Please check for details"+image_file.errorString());
        return image_file;
    }

    QImageReader image_reader(&image_file);

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
        return image_file;
    }

    file_map_.insert(image_file.fileName());
    image_file.close();

    return image_file;
}

QMap<QString, QMap<QString, QList<QString> > > FileReadSystem::ReadJsonFile(QFile json_file)
{
    QMap<QString, QMap<QString,QList<QString> >> json_map;
    if(!json_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Failed to open the file");
        return json_map;
    }

    QByteArray json_data=json_file.readAll();
    json_file.close();

    QJsonParseError json_error;
    QJsonDocument json_doc=QJsonDocument::fromJson(json_data,&json_error);
    if(json_error.error!=QJsonParseError::NoError)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,json_error.errorString());
        return json_map;
    }

    ParseJson(json_doc.object(),json_map);

    file_map_.insert(json_file.fileName());
    return json_map;
}

void FileReadSystem::ParseJson(const QJsonObject &json_obj, QMap<QString, QMap<QString, QList<QString> > > &json_map)
{
    QStringList keys = json_obj.keys();

    for (const QString &key : keys)
    {
        QJsonValue value = json_obj[key];

        if (key.isEmpty())
        {
            FileWirteSystem::OutMessage(FileWirteSystem::Debug, "Json key is null");
            continue;
        }

        QMap<QString, QList<QString>> nested_map;
        QList<QString> list_value;

        if (value.isArray())
        {
            ParseJsonArray(value.toArray(), nested_map,key,list_value);
        }
        else if (value.isObject())
        {
            ParseJsonObject(value.toObject(), nested_map,key,list_value);
        }
        else
        {
            QList<QString> relative_paths;
            relative_paths.append(value.toString());
            nested_map.insert(key, relative_paths);
        }

        json_map.insert(key, nested_map);
    }
}

void FileReadSystem::ParseJsonObject(const QJsonObject& json_obj, QMap<QString, QList<QString>> &nested_map,const QString &parent_key,QList<QString>& list_value)
{
    QStringList keys = json_obj.keys();

    for (const QString &key : keys)
    {
        QJsonValue value = json_obj[key];

        if (key.isEmpty())
        {
            FileWirteSystem::OutMessage(FileWirteSystem::Debug, "Json key is null");
            continue;
        }

        QMap<QString,QList<QString>> relative_paths;

        if (value.isArray())
        {
            ParseJsonArray(value.toArray(), relative_paths,key,list_value);
        }
        else if (value.isObject())
        {
            ParseJsonObject(value.toObject(), relative_paths,key,list_value);
        }
        else
        {
            QList<QString> nested_relative_paths;
            nested_relative_paths.append(value.toString());
            relative_paths.insert(key,nested_relative_paths);
        }

        list_value.clear();
        nested_map.insert(relative_paths);

    }
}

void FileReadSystem::ParseJsonArray(const QJsonArray& json_array, QMap<QString,QList<QString>>& relative_paths,const QString &key,QList<QString>& list_value)
{
    for(const QJsonValue& sub_value:json_array)
    {
        if(sub_value.isArray())
        {
            ParseJsonArray(sub_value.toArray(),relative_paths,key,list_value);
        }
        else if(sub_value.isObject())
        {
            ParseJsonObject(sub_value.toObject(),relative_paths,key,list_value);
        }

        list_value.append(sub_value.toString());
        relative_paths.insert(key,list_value);
    }
}

QString FileReadSystem::ReadFileContentsToString(QFile &file)
{
    if(file.fileName().isEmpty()||file_map_.contains(file.fileName()))
    {
        return QString();
    }

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Failed to open the: "+file.fileName()+"file");
        return QString();
    }

    QString file_content=file.readAll();
    if(file_content.isEmpty())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"The file content is empty, the file name is: "+file.fileName());
        file.close();
        return QString();
    }

    file.close();
    file_map_.insert(file.fileName());
    return file_content;
}

void FileReadSystem::ReadResourcesTypeFilesFormJson(QMap<QString, QList<QString> > json_map, resourcesfiletype::ResourcesType type)
{
    if(json_map.isEmpty())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Read json file is null");
        return;
    }

    QList<QString> keys = json_map.keys();

    for (const QString &key : keys)
    {
        QList<QString> relativePaths = json_map.value(key);
        // Store new file contents
        QList<QString> value_codes;
        // Determine whether you want to replace it
        bool if_file=true;

        for (QString &relativePath : relativePaths)
        {
            QString file_code = FilePathSystem::GetResourcesPath(type,relativePath);
            QFile file(file_code);
            QString value_code = ReadFileContentsToString(file);
            if(value_code.isEmpty()&&value_codes.isEmpty())
            {
                if_file=false;
            }
            else
            {
                if_file=true;
                value_codes.push_back(value_code);
            }
        }

        if(if_file)
        {
            json_map.insert(key,value_codes);
        }
    }
}

void FileReadSystem::ReadResourcesTypeFilesFormJson(QMap<QString, QList<QString> > json_map)
{
    if(json_map.isEmpty())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Read json file is null");
        return;
    }

    QList<QString> keys = json_map.keys();

    for (const QString &key : keys)
    {
        QList<QString> relativePaths = json_map.value(key);
        // Store new file contents
        QList<QString> value_codes;
        // Determine whether you want to replace it
        bool if_file=true;

        for (QString &relativePath : relativePaths)
        {
            QString file_code = FilePathSystem::GetResourcesPath(key,relativePath);
            QFile file(file_code);
            QString value_code = ReadFileContentsToString(file);
            if(value_code.isEmpty()&&value_codes.isEmpty())
            {
                if_file=false;
            }
            else
            {
                if_file=true;
                value_codes.push_back(value_code);
            }
        }

        if(if_file)
        {
            json_map.insert(key,value_codes);
        }
    }
}
