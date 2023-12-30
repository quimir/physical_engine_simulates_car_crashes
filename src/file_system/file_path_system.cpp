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

#include "src_include/file_system/file_path_system.h"
#include <QResource>
#include <QStandardPaths>

QString FilePathSystem::GetPath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+name);
}

QString FilePathSystem::GetResourcesPath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+"resources"+QDir::separator()+name);
}

QString FilePathSystem::GetLogsPath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+"logs"+QDir::separator()+name);
}

QString FilePathSystem::GetResourcesPath(resourcesfiletype::ResourcesType type, const QString& name, bool suffix)
{
    if(suffix)
    {
        return resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToStringPath(type)+name
               +resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToString(type).toLower();
    }

    return resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToStringPath(type)+name;
}

QString FilePathSystem::RCCToAbsolutePath(const QString &rcc_path)
{
    return QFileInfo(QResource(rcc_path).fileName()).absoluteFilePath();
}

QString FilePathSystem::GetResourcesPath(const QString &type, const QString &name)
{
    return resourcesfiletype::ResourcesTypeToMapper::GetInstance().StringToEnumToStringPath(type)+name;
}

FilePathSystem &FilePathSystem::GetInstance()
{
    return Instance();
}

FilePathSystem &FilePathSystem::Instance()
{
    static FilePathSystem instance;
    return instance;
}

QString FilePathSystem::GetRoot()
{
    static QString logl_root;
    static bool initalized=false;
    if(!initalized)
    {
        QDir app_dir(QCoreApplication::applicationDirPath());
        // Navigate to the parent directory
        app_dir.cdUp();
        // Navigate to the configuration directory
        app_dir.cd("configuration");
        QFile config_file(app_dir.filePath("root_directory.h"));
        if(config_file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QTextStream in(&config_file);
            while(!in.atEnd())
            {
                QString line=in.readLine();
                if(line.startsWith("const char * logl_root ="))
                {
                    int start_index=line.indexOf("\"")+1;
                    int end_index=line.lastIndexOf("\"");
                    logl_root=line.mid(start_index,end_index-start_index);
                    break;
                }
            }
            config_file.close();
        }
        else
        {
            app_dir.cdUp();
            // Handle error opeing file
            logl_root=app_dir.path();// Use the application directory as the root
        }
        initalized=true;
    }
    return logl_root;
}
