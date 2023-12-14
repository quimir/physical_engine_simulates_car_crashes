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
 * @file       file_path_system.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#include "src_include/file_path_system.h"

QString FilePathSystem::GetPath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+name);
}

QString FilePathSystem::GetImagePath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+"resources"+QDir::separator()+name);
}

QString FilePathSystem::GetAttributesSettingPath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+"resources"+QDir::separator()+"attributes _beautify_files"+QDir::separator()+name);
}

QString FilePathSystem::GetShaderPath(const QString &name)
{
    return QDir::toNativeSeparators(GetRoot()+QDir::separator()+"src"+QDir::separator()+"shader"+QDir::separator()+name);
}

QString FilePathSystem::GetRoot()
{
    static QString logl_root;
    static bool initalized=false;
    if(!initalized)
    {
        QDir app_dir(QCoreApplication::applicationDirPath());
        app_dir.cdUp();// Navigate to the parent directory
        app_dir.cd("configuration"); // Navigate to the configuration directory
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
