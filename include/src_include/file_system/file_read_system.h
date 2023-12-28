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
    QString LoadStylesFromFile(const QString&file_name);

    QImage ReadImageFile(const QString& file_path);

    QImage ReadImageFile(QFile &image_file);

    /**
     * @brief ReadFileContentsToString Reads the contents of a file into a string.
     * @param file File path.
     * @return The entire contents of the file.
     */
    QString ReadFileContentsToString(QFile& file);

    QMap<QString,QMap<QString,QList<QString>>> ReadGLSLFile(QMap<QString,QMap<QString,QList<QString>>>& glsl_map
                                                              ,resourcesfiletype::ResourcesType type=resourcesfiletype::ResourcesType::GLSL);

    /**
     * @brief ReadJsonFile Read the Json file and return to go out, the content of the Json file format, please check /resources/Json/README.md Content.
     * @param json_file Target jsonfile
     * @return Returns a combination of key-key-array values, ensuring that the first key is unique.
     */
    QMap<QString,QMap<QString,QList<QString>>> ReadJsonFile(QFile json_file);

    static FileReadSystem& GetInstance();

private:
    void ParseJson(const QJsonObject& json_obj,QMap<QString, QMap<QString, QList<QString> > > &json_map);
    void ParseJsonObject(const QJsonObject& json_object, QMap<QString,QList<QString>>& relative_paths
                         ,const QString &key,QList<QString>& value);
    void ParseJsonArray(const QJsonArray& json_array, QMap<QString,QList<QString>>& relative_paths,const QString &key
                        , QList<QString>& list_value);
private:
    static FileReadSystem& Instance();

    inline FileReadSystem():file_map_(QSet<QString>())
        {};

    /**
     * @brief file_map_ Store all the files that have been read so that they don't have to be read again
     */
    QSet<QString> file_map_;
};

#endif // FILE_SYSTEM_FILE_READ_SYSTEM_H
