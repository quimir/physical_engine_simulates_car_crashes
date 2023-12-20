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

#ifndef FILE_READ_SYSTEM_H
#define FILE_READ_SYSTEM_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QImageReader>
#include <QMap>
#include <QVector>
#include <QMultiMap>
#include "src_include/resources_file_type.h"

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
     * @brief ReadJsonFile Read the entire contents of the json file, and store the key and value in the json into the Map.
     * @param json_file The json file can be a relative path in the.qrc or an absolute path and a relative path to the project.
     * @return Stores all json as a map of all keys and values
     */
    static QMap<QString,QList<QString>> ReadJsonFile(QFile json_file);

private:
    /**
     * @brief ParseJson We iterate over all the keys and values in the json file.
     * If the value below the key is an array, we pass it to ParseJsonArray,
     * and if it's an object, we continue processing until we have a single key and a single value.
     * @param json_obj Json object
     * @param json_map A map that stores all the keys and values in the json
     */
    static void ParseJson(const QJsonObject& json_obj,QMap<QString,QList<QString>>& json_map);

    /**
     * @brief ParseJsonArray Same logic as ParseJson, but it adds the key and value to the map
     * @param json_array json array to read
     * @param json_map json map of the records
     * @param key json key
     */
    static void ParseJsonArray(const QJsonArray& json_array,QMap<QString,QList<QString>>& json_map,const QString& key);
private:
    /**
     * @brief file_map_ Store all the files that have been read so that they don't have to be read again
     */
    static QSet<QString> file_map_;
};

#endif // FILE_READ_SYSTEM_H
