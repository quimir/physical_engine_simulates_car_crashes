#include "src_include/filepathsystem.h"

QString FilePathSystem::GetPath(const QString &path)
{
    QString root=GetRoot();
    return QDir::toNativeSeparators(root+QDir::separator()+path);
}

QString FilePathSystem::GetImagePath(const QString &path)
{
    QString root=GetRoot();
    return QDir::toNativeSeparators(root+QDir::separator()+"resources"+QDir::separator()+path);
}

QString FilePathSystem::GetAttributesSettingPath(const QString &path)
{
    QString root=GetRoot();
    return QDir::toNativeSeparators(root+QDir::separator()+"resources"+QDir::separator()+"attributes _beautify_files"+QDir::separator()+path);
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
