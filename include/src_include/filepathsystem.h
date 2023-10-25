#ifndef FILEPATHSYSTEM_H
#define FILEPATHSYSTEM_H

#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

class FilePathSystem
{
public:
    static QString GetPath(const QString&path);
    static QString GetImagePath(const QString &path);
    static QString GetAttributesSettingPath(const QString &path);

private:
    static QString GetRoot();

};

#endif // FILEPATHSYSTEM_H
