#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "./src_include/mainwindow.h"
#include "src_include/filewirtesystem.h"

#include "src_include/firstpersoncamera.h"

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

    qInstallMessageHandler(FileWirteSystem::CustomMessageHandler);
    FileWirteSystem::DeleteLogDay(FileWirteSystem::log_file_,1);
    MainWindow w;
    w.show();
    FileWirteSystem::EndWirteLine();
    return a.exec();
}
