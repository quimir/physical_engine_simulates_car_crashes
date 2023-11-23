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
 * @file       mainwindow.cpp
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#include "./src_include/mainwindow.h"
#include "./ui_mainwindow.h"
#include "src_include/mainentrybutton.h"
#include "src_include/setting_window//settingwindow.h"
#include "src_include/filewirtesystem.h"
#include "src_include/filepathsystem.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("汽车仿真碰撞引擎");
    GetScreenWindow();
    SetUIWindow();
}

void MainWindow::GetScreenWindow()
{
    QScreen* user_screen = QGuiApplication::primaryScreen();
    QRect get_user_screen = user_screen->availableGeometry();
    this->screen_width_ = get_user_screen.width();
    this->screen_height_ = get_user_screen.height();
    FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("User screen width: %1,height: %2")
                                .arg(QString::number(screen_width_), QString::number(screen_height_)));
}

int MainWindow::GetScreenHeight()const
{
    return this->screen_height_;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug,"The user closes the window using the close event in the upper-right corner");
    FileWirteSystem::EndWirteLine();
}

int MainWindow::GetScreenWidth()const
{
    return this->screen_width_;
}

void MainWindow::PlaceStartButton()
{
    /*
     * --- Sets the basic properties of the start button--------
    */

    MainEntryButton* start_button = new MainEntryButton(FilePathSystem::GetImagePath("start.png"),
                                                        QSize((this->width() / 2 - this->width() / 10 * 3), this->height() / 8)
                                                        , "开始");
    start_button->move(QPoint((this->width() / 16), (this->height() - this->height() / 4)));
    start_button->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);"
                                "border:2px groove gray;border-radius:10px;"
                                "padding:2px 4px;border-style: outset;}"
                                "QPushButton:hover{background-color:rgb(229, 241, 251); "
                                "color: black;}"
                                "QPushButton:pressed{background-color:rgb(204, 228, 247);"
                                "border-style: inset;}");
    start_button->setFocusPolicy(Qt::NoFocus);
    start_button->installEventFilter(this);
    start_button->setParent(this);


    connect(start_button, &QPushButton::clicked, [=]() {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug, "clicked start_button");
    });
}

void MainWindow::PlaceSettingButton()
{
    MainEntryButton* setting_button = new MainEntryButton(FilePathSystem::GetImagePath("setting.png"),
                                                          QSize(this->width() / 2 - this->width() / 10 * 3, this->height() / 8)
                                                          , "设置");
    setting_button->move(QPoint(this->width() / 2 - this->width() / 9, this->height() - this->height() / 4));
    setting_button->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);"
                                  "border:2px groove gray;border-radius:10px;"
                                  "padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(229, 241, 251); "
                                  "color: black;}"
                                  "QPushButton:pressed{background-color:rgb(204, 228, 247);"
                                  "border-style: inset;}");
    setting_button->setFocusPolicy(Qt::NoFocus);
    setting_button->installEventFilter(this);
    setting_button->setParent(this);

    SettingWindow* setting_window = new SettingWindow(this->geometry());

    connect(setting_button, &QPushButton::clicked, setting_window, [=]() {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug, "clicked setting_button");

        QTimer::singleShot(200, this, [=]() {
            this->hide();
            setting_window->show();
        });

    });
}

void MainWindow::PlaceEndButton()
{
    MainEntryButton* end_button = new MainEntryButton(FilePathSystem::GetImagePath("end.png"),
                                                      QSize(this->width() / 2 - this->width() / 10 * 3, this->height() / 8)
                                                      , "退出");
    end_button->move(QPoint(this->width() - this->width() / 3.5, this->height() - this->height() / 4));
    end_button->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);"
                              "border:2px groove gray;border-radius:10px;"
                              "padding:2px 4px;border-style: outset;}"
                              "QPushButton:hover{background-color:rgb(229, 241, 251); "
                              "color: black;}"
                              "QPushButton:pressed{background-color:rgb(204, 228, 247);"
                              "border-style: inset;}");
    end_button->setFocusPolicy(Qt::NoFocus);
    end_button->installEventFilter(this);
    end_button->setParent(this);

    connect(end_button, &QPushButton::clicked, this, [=]() {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug, "clicked end_button");
        FileWirteSystem::EndWirteLine();
        this->close();
    });
}

void MainWindow::SetUIWindow()
{
    this->setGeometry(GetScreenWidth() / 4, GetScreenHeight() / 4, GetScreenWidth() / 2, GetScreenHeight() / 2);
    FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Now main_windows width: %1 height: %2")
                                                            .arg(QString::number(this->width()),QString::number(this->height())));
    PlaceStartButton();
    PlaceSettingButton();
    PlaceEndButton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

