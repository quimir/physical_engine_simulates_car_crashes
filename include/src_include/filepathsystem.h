/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       filepathsystem.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/26
 * @history
 *****************************************************************************/


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
