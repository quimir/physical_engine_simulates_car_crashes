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


#define QT_NO_DEBUG_OUTPUT
#define QT_NO_QML_DEBUG

#include <QApplication>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QResource>

#include "src_include/main_window.h"
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/json_type/json_type.h"
#include "src_include/file_system/file_path_system.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "physical_engine_simulates_car_crashes_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    jsontype::JsonType::GetInstance(
        FilePathSystem::GetInstance().GetResourcesPath(
            resourcesfiletype::ResourcesType::kJson,"index.json"));

    qInstallMessageHandler(FileWriteSystem::CustomMessageHandler);
    FileWriteSystem::GetInstance().RemoveDefaultLogFile();

    MainWindow w;
    w.show();
    return a.exec();
}
