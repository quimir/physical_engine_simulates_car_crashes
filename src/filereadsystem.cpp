#include "src_include/filereadsystem.h"
#include "src_include/filewirtesystem.h"

FileReadSystem::FileReadSystem()
{

}

QString FileReadSystem::LoadStylesFromFile(const QString &file_name)
{
    QString styles;
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream steam(&file);
    }

    return "";
}
