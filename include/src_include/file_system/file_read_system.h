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
    /**
     * @brief GetInstance The only way to access an object of class
     * FileReadSystem, no other method can access its object,
     * and the only way to call a function of class FileReadSystem.
     * @return FileReadSystem unique object.
     */
    static FileReadSystem& GetInstance();

    /**
     * @brief ReadImageFile It reads the information about the image, prints
     * the attributes of the image after loading, and returns QImage if
     * there is no information about the image.
     * @param file_path Path to the image file
     * @return On success, it returns a loaded and ready to use QImage
     * object; otherwise, it returns an empty QImage object.
     */
    QImage ReadImageFile(const QString& file_path);

    /**
     * @brief ReadImageFile It reads the information about the image,
     * prints the attributes of the image after loading, and returns QImage
     * if there is no information about the image.
     * @param image_file Path to the image file
     * @return On success, it returns a loaded and ready to use
     * QImage object; otherwise, it returns an empty QImage object.
     */
    QImage ReadImageFile(QFile& image_file);

    /**
     * @brief ReadFileContentsToString Reads the contents of a
     * file into a string.
     * @param file File path.
     * @return The entire contents of the file.
     */
    QString ReadFileContentsToString(QFile& file);

    /**
     * @brief ReadGLSLFile Read the map from the json, and if the
     * keyword GLSL is found, convert the file path to the file content
     * and re-store it into the map.
     * @param glsl_map A map read from json
     * @param type Generally, the default is GLSL
     * @return Modified json map.
     */
    QMap<QString,QMap<QString,QList<QString>>> ReadGLSLFile(
        QMap<QString,QMap<QString,QList<QString>>>& glsl_map,
        resourcesfiletype::ResourcesType type=
        resourcesfiletype::ResourcesType::kGLSL);

    /**
     * @brief ReadJsonFile Read the Json file and return to go out, the
     * content of the Json file format, please check
     * /resources/Json/README.md Content.
     * @param json_file Target jsonfile
     * @return Returns a combination of key-key-array values, ensuring that
     * the first key is unique.
     */
    QMap<QString,QMap<QString,QList<QString>>> ReadJsonFile(QFile json_file);

    /**
     * @brief ReadJsonFileToJsonObject Read all the data from the Json
     * class file (if the file path is correct and conforms to the
     * Json class file specification) into the QJsonObject object.
     * @param json_path
     * @return
     */
    QJsonObject ReadJsonFileToJsonObject(const QString& json_path);

    QJsonObject ReadJsonFileToJsonObject(QFile json_file);

    /**
     * @brief ReadFileFirstLine Reads the first part of the file and stores
     * it all in a string.
     * @param file A file that needs to be read
     * @param first_line First line of information
     * @return Returns true on success, false otherwise.
     */
    bool ReadFileFirstLine(QFile& file,QString& first_line);

    /**
     * @brief ReadFileFirstLine Reads the first part of the file and
     * stores it all in a string.
     * @param file_path The path to the file.
     * @param first_line First line of information.
     * @return Returns true on success, false otherwise.
     */
    bool ReadFileFirstLine(const QString& file_path,QString& first_line);

private:
    /* The following functions are not recommended to be modified unless
     * you are familiar with the function and its logic. */
    void ParseJson(const QJsonObject& json_obj,
                   QMap<QString, QMap<QString,QList<QString>>>& json_map);

    void ParseJsonObject(const QJsonObject& json_object,
                         QMap<QString,QList<QString>>& relative_paths,
                         const QString &key,QList<QString>& value);

    void ParseJsonArray(const QJsonArray& json_array,
                        QMap<QString,QList<QString>>& relative_paths,
                        const QString &key, QList<QString>& list_value);

    /* End */
private:
    /**
     * @brief Instance Initialize the FileReadSystem's unique object.
     * @return FileReadSystem's unique object.
     */
    static FileReadSystem& Instance();

    /**
     * @brief FileReadSystem Initialize the data in the FileReadSystem.
     */
    inline FileReadSystem():file_map_(QSet<QString>())
        {};

private:
    /**
     * @brief file_map_ Store all the files that have been read so that they don't have to be read again
     */
    QSet<QString> file_map_;
};

#endif // FILE_SYSTEM_FILE_READ_SYSTEM_H
