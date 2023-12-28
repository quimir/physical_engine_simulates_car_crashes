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

#ifndef FILE_SYSTEM_FILE_READ_SYSTEM_H
#define FILE_SYSTEM_FILE_READ_SYSTEM_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QImageReader>
#include <QMap>
#include <QVector>
#include <QMultiMap>
#include "src_include/file_system/resources_file_type.h"

class FileReadSystem
{
public:
    FileReadSystem()=delete;

    static QString LoadStylesFromFile(const QString&file_name);

    /**
     * @brief ReadImageFile Read whether the system meets the loading requirements of the image,
     * if it meets the address of the original file,
     * you can use the file path of.qrc or the absolute path and relative path
     * @param file_path The path to the image file
     * @return file_path
     */
    static QString ReadImageFile(const QString& file_path);

    /**
     * @brief ReadImageFile Read whether the system meets the loading requirements of the image,
     * if it meets the address of the original file
     * @param image_file picture file
     * @return image_file
     */
    static QFile& ReadImageFile(QFile& image_file);

    /**
     * @brief ReadFileContentsToString Reads the contents of a file into a string.
     * @param file File path.
     * @return The entire contents of the file.
     */
    static QString ReadFileContentsToString(QFile& file);

    /**
     * @brief ReadResourcesTypeFilesFormJson In general, before using this function, you need to use ReadJsonFile to get the json map. Using this function,
     * all the values corresponding to the key can be converted from the relative path of the resource file to the entire contents of the file and
     * all the values in the key can be replaced.
     * @param json_map Stores all the keys and values in json.
     * @param type For the type of the resource path, see ResourcesType.
     */
    static void ReadResourcesTypeFilesFormJson(QMap<QString,QList<QString>> json_map,resourcesfiletype::ResourcesType type);

    /**
     * @brief ReadResourcesTypeFilesFormJson Automatically link the contents of any type of file in the resource system, but for now, it is only string friendly,
     * and the rest is not very useful unless you want to increase the coupling of the code.
     * @param json_map Stores all the keys and values in json.
     */
    static void ReadResourcesTypeFilesFormJson(QMap<QString,QList<QString>> json_map);

    static QMap<QString,QMap<QString,QList<QString>>> ReadJsonFile(QFile json_file);

private:
    static void ParseJson(const QJsonObject& json_obj,QMap<QString, QMap<QString, QList<QString> > > &json_map);
    static void ParseJsonObject(const QJsonObject& json_object, QMap<QString,QList<QString>>& relative_paths,const QString &key,QList<QString>& value);
    static void ParseJsonArray(const QJsonArray& json_array, QMap<QString,QList<QString>>& relative_paths, const QString &key, QList<QString>& list_value);
private:
    /**
     * @brief file_map_ Store all the files that have been read so that they don't have to be read again
     */
    static QSet<QString> file_map_;
};

#endif // FILE_SYSTEM_FILE_READ_SYSTEM_H
