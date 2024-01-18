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
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/file_path_system.h"
#include <QJsonArray>
#include <QJsonDocument>

QImage FileReadSystem::ReadImageFile(const QString &file_path)
{
    if(file_path.isEmpty())
    {
        // eturns an invalid QImage
        return QImage();
    }

    if (file_map_.contains(file_path))
    {
        // Returns the original value
        return QImage(file_path);
    }

    QImageReader image_reader(file_path);
    QImage image;

    if (!QFile::exists(file_path))
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  , file_path + " failed to open the file. Please check for details: " + image_reader.errorString());
        return QImage();  // eturns an invalid QImage
    }

    if (!image_reader.format().isEmpty())
    {
        image = image_reader.read();
        if (image.isNull())
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                      "Failed to read image: " + image_reader.errorString());
            return QImage();  // eturns an invalid QImage
        }
        
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  , "Image name: " + image_reader.fileName() +
                                                      ", picture format: " + QString::fromStdString(image_reader.format().toStdString()) +
                                                      ", file width: " + QString::number(image.width()) +
                                                      ", height: " + QString::number(image.height()));
    }
    else
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                  "The picture cannot be read because: " + image_reader.errorString());
        return QImage();  // eturns an invalid QImage
    }

    file_map_.insert(file_path);
    return image;
}

QImage FileReadSystem::ReadImageFile(QFile &image_file)
{
    if(image_file.fileName().isEmpty())
    {
        return QImage();
    }

    if (file_map_.contains(image_file.fileName()))
    {
        return QImage(image_file.fileName());
    }

    if (!image_file.exists())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                  image_file.fileName()
                                                      + " failed to open the file. Please check for details: " + image_file.errorString());
        return QImage();
    }

    if (!image_file.open(QIODevice::ReadOnly))
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                  "Failed to open file: "
                                                      + image_file.fileName());
        return QImage();
    }

    QImageReader image_reader(&image_file);

    if (!image_reader.format().isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                  "Image name: " + image_reader.fileName() +
                                                      ", picture format: " + QString::fromStdString(image_reader.format().toStdString()) +
                                                      ", file width: " + QString::number(image_reader.size().width()) +
                                                      ", height: " + QString::number(image_reader.size().height()));

        QImage image = image_reader.read();
        file_map_.insert(image_file.fileName());
        image_file.close();
        return image;
    }
    else
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,
                                                  "The picture cannot be read because: " + image_reader.errorString());
        image_file.close();
        return QImage();
    }
}

QMap<QString, QMap<QString, QList<QString> > > FileReadSystem::ReadJsonFile(QFile json_file)
{
    QMap<QString, QMap<QString,QList<QString> >> json_map;
    if(!json_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,"Failed to open the file");
        return json_map;
    }

    QByteArray json_data=json_file.readAll();
    json_file.close();

    QJsonParseError json_error;
    QJsonDocument json_doc=QJsonDocument::fromJson(json_data,&json_error);
    if(json_error.error!=QJsonParseError::NoError)
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,json_error.errorString());
        return json_map;
    }

    ParseJson(json_doc.object(),json_map);

    file_map_.insert(json_file.fileName());
    return json_map;
}

bool FileReadSystem::ReadFileFirstLine(QFile &file, QString &first_line)
{
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        if(!in.atEnd())
        {
            first_line=in.readLine();
            file.close();
            return true;
        }
        file.close();
    }
    return false;
}

bool FileReadSystem::ReadFileFirstLine(const QString &file_path, QString &first_line)
{
    if(file_path.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"File path is null!");
        return false;
    }

    QFile file(file_path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        if(!in.atEnd())
        {
            first_line=in.readLine();
            file.close();
            return true;
        }
        file.close();
    }
    return false;
}

FileReadSystem &FileReadSystem::GetInstance()
{
    return Instance();
}

void FileReadSystem::ParseJson(const QJsonObject &json_obj, QMap<QString, QMap<QString, QList<QString> > > &json_map)
{
    QStringList keys = json_obj.keys();

    for (const QString &key : keys)
    {
        QJsonValue value = json_obj[key];

        if (key.isEmpty())
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug, "Json key is null");
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
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug, "Json key is null");
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
    }

    if(!list_value.isEmpty())
    {
        relative_paths.insert(key,list_value);
    }
}

FileReadSystem &FileReadSystem::Instance()
{
    static FileReadSystem instance;
    return instance;
}

QString FileReadSystem::ReadFileContentsToString(QFile &file)
{
    if(file_map_.contains(file.fileName()))
    {
        return QString();
    }

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,"Failed to open the: "+file.fileName()+"file");
        file_map_.insert(file.fileName());
        return QString();
    }

    QString file_content=file.readAll();
    if(file_content.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,"The file content is empty, the file name is: "+file.fileName());
        file_map_.insert(file.fileName());
        file.close();
        return QString();
    }

    file.close();
    return file_content;
}

QMap<QString, QMap<QString, QList<QString>>> FileReadSystem::ReadGLSLFile(QMap<QString, QMap<QString, QList<QString> > > &glsl_map, resourcesfiletype::ResourcesType type)
{
    if(glsl_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"GLSL map is null!");
        return glsl_map;
    }

    // Get all the keys
    QMap<QString,QMap<QString,QList<QString>>>::Iterator it=glsl_map.begin();

    while(it!=glsl_map.end())
    {
        // Matches are performed regardless of case requirements
        if(!QString::compare(it.key(),resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToString(type),Qt::CaseInsensitive))
        {
            QMap<QString,QList<QString>> temp;
            // Translate all the relative paths into text and save them there
            QMap<QString,QList<QString>> value=it.value();
            QList<QString> keys=value.keys();
            for(const QString&key:keys)
            {
                // Gets the value of the relative path
                QList<QString> relative_paths=value.value(key);
                QList<QString> value_codes;
                bool if_file=true;

                for(QString &relative_path:relative_paths)
                {
                    QString file_code=FilePathSystem::GetInstance().GetResourcesPath(type,relative_path);
                    QFile file(file_code);
                    QString value_code=ReadFileContentsToString(file);
                    // If they are all empty then nothing is saved
                    if(value_code.isEmpty()&&value_codes.isEmpty())
                    {
                        if_file=false;
                    }
                    else
                    {
                        // If one of these matches, you have to update to one of them
                        if_file=true;
                        value_codes.push_back(value_code);
                    }
                }
                if(if_file)
                {
                    temp.insert(key,value_codes);
                }
            }
            glsl_map.insert(resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToString(type),temp);
            break;
        }
        it++;
    }

    return glsl_map;
}
