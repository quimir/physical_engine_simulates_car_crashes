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

#ifndef FILE_SYSTEM_FILE_PATH_SYSTEM_H
#define FILE_SYSTEM_FILE_PATH_SYSTEM_H

#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include "src_include/file_system/resources_file_type.h"

/**
 * @brief The FilePathSystem class his class has been largely replaced
 * by RCC'S resource management SYSTEM, only SOME FUNCTIONS ARE STILL
 * available. Please specify your own information if you want to use
 * this class.
 */
class FilePathSystem
{
public:
    /**
     * @brief GetInstance The only way to access an object of class
     * FilePathSystem, no other method can access its object, and the
     * only way to call a function of class FilePathSystem.
     * @return Unique object.
     */
    static FilePathSystem& GetInstance();

    /**
     * @brief GetPath Returns the top-level directory of the project + name.
     * @param name File name.
     * @return Top-level directory + name of the project.
     */
    QString GetPath(const QString&name);

    /**
     * @brief GetResourcesPath Return the absolute path under the
     * Resources folder,that is: the absolute path of the project + the
     * absolute path location of the Resources in the project + the file
     * name.
     * @param name The name of the desired file.
     * @return the absolute path of the project + the absolute path location
     *  of the Resources in the project + the file name.
     */
    QString GetResourcesPath(const QString &name);

    /**
     * @brief GetLogsPath Returns the absolute path to the requirements
     * in the logs folder of this project.
     * @param name The name of the desired file
     * @return the absolute path of the project + the absolute path location
     * of the logs in the project + the file name.
     */
    QString GetLogsPath(const QString& name);

    /**
     * @brief GetResourcesPath Returns the location of the file relative to
     * the RCC resource system under the RCC resource system.
     * @param type For the types of RCC resource files, see the
     * ResourcesType enumeration class for details.
     * @param name Name of the file.
     * @param suffix Autofill file type, which is still experimental
     * and not ope.
     * @return RCC relative path + name.
     */
    QString GetResourcesPath(resourcesfiletype::ResourcesType type,
                             const QString &name,bool suffix=false);

    /**
     * @brief RCCToAbsolutePath The absolute path from the relative path of
     * RCC to the binary form of the file,for example: /RCC/.... in RCC
     * After parsing, you get: project build path +....
     * @param rcc_path The relative path of the file in RCC
     * @return The absolute path of the file on the system
     */
    QString RCCToAbsolutePath(const QString& rcc_path);

    QString ExtractResource(const QString& resource_path,
                            const QString& destination_dir);

    /**
     * @brief IsRccPath The index in front of the path is used
     * to determine whether it is a path of RCC.
     * @param path The path to the file.
     * @return If it is true, otherwise it returns false.
     */
    bool IsRccPath(const QString& path);

    /**
     * @brief IsAbsolutePath Use Qt's own filesystem to check
     * whether the path is an absolute path.See the QFileInfo
     * class for details.
     * @param path The path to the file.
     * @return If it is true, otherwise it returns false.
     */
    bool IsAbsolutePath(const QString& path);

    /**
     * @brief IsRelativePath By checking whether the path is an
     * RCC file path and an absolute path to determine whether
     * it is a relative path, when the RCC file path and the
     * absolute path are both false, then it is a relative path.
     * @param path The path to the file.
     * @return If it is true, otherwise it returns false.
     */
    bool IsRelativePath(const QString& path);

    /**
     * @brief GetResourcesPath Returns the location of the file relative
     * to the RCC resource system under the RCC resource system.
     * @param type For the types of RCC resource files, see the
     * ResourcesType enumeration class for details
     * @param name Name of the file
     * @return RCC relative path + name
     */
    QString GetResourcesPath(const QString& type,const QString& name);

private:
    /**
     * @brief Instance Gets the unique object of the FilePathSystem
     * @return Unique object.
     */
    static FilePathSystem& Instance();

    inline FilePathSystem()
        {};

    /**
     * @brief GetRoot Returns the absolute path of the item in the system,
     * which is the core code of the class.
     * @return The absolute path for this item in the system
     */
    QString GetRoot();

};

#endif // FILE_SYSTEM_FILE_PATH_SYSTEM_H
