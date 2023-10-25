#ifndef FILEREADSYSTEM_H
#define FILEREADSYSTEM_H

#include <QString>
#include <QFile>
#include <QTextStream>

class FileReadSystem
{
public:
    FileReadSystem();

    static QString LoadStylesFromFile(const QString&file_name);
};

#endif // FILEREADSYSTEM_H
