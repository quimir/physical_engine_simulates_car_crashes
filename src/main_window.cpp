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

#include "src_include/main_window.h"
#include "qapplication.h"
#include "src_include/main_entry_button.h"
#include "src_include/setting_window/setting_window.h"
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/file_path_system.h"
#include <QQmlApplicationEngine>
#include <QJsonArray>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("汽车仿真碰撞引擎");
    this->buttons_.resize(3);
    GetScreenWindow();
    SetUIWindow();
    auto shader_file=FileReadSystem::GetInstance().ReadJsonFile(FilePathSystem::GetInstance().GetResourcesPath(resourcesfiletype::ResourcesType::Json,"data.json"));
    FileReadSystem::GetInstance().ReadGLSLFile(shader_file);
    for(MainEntryButton* button:this->buttons_)
    {
        connect(button,&MainEntryButton::clicked,this,&MainWindow::HandleButtonClicked);
    }
}

void MainWindow::GetScreenWindow()
{
    QScreen* user_screen = QApplication::primaryScreen();
    QRect get_user_screen = user_screen->availableGeometry();
    this->screen_width_ = get_user_screen.width();
    this->screen_height_ = get_user_screen.height();
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                              , QString("User screen width: %1,height: %2")
                                                  .arg(QString::number(screen_width_), QString::number(screen_height_)));
}

int MainWindow::GetScreenHeight()const
{
    return this->screen_height_;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                              ,"The user closes the window using the close event in the upper-right corner");
    FileWriteSystem::GetInstance().EndWirteLine();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPixmap background_image=QPixmap::fromImage(FileReadSystem::GetInstance().ReadImageFile(FilePathSystem::GetInstance().GetResourcesPath(resourcesfiletype::ResourcesType::Image,"background_picture.png")));

    if(background_image.isNull())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"The background image fails to be read. Check the cause of the failure");
    }

    QBrush brush(background_image);
    QPainter painter(this);
    painter.fillRect(this->rect(),brush);

    QMainWindow::paintEvent(event);
}

int MainWindow::GetScreenWidth()const
{
    return this->screen_width_;
}

void MainWindow::SetUIWindow()
{
    this->setGeometry(GetScreenWidth() / 4, GetScreenHeight() / 4, GetScreenWidth() / 2, GetScreenHeight() / 2);
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                              ,QString("Now main_windows width: %1 height: %2")
                                                  .arg(QString::number(this->width()),QString::number(this->height())));
    CreateWindowButton();
}

void MainWindow::HandleButtonClicked()
{
    MainEntryButton *clicked_button=qobject_cast<MainEntryButton*>(sender());
    if(nullptr==clicked_button)
        return;

    if(clicked_button==this->buttons_[0])
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug, "clicked start_button");
    }
    else if(clicked_button==this->buttons_[1])
    {
        SettingWindow* setting_window=new SettingWindow(this->geometry());
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug, "clicked setting_button");

        QTimer::singleShot(200, this, [=]() {
            setting_window->show();
            this->close();
        });
    }
    else if(clicked_button==this->buttons_[2])
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug, "clicked end_button");
        FileWriteSystem::GetInstance().EndWirteLine();
        this->close();
    }
}

MainWindow::~MainWindow()
{
    for(MainEntryButton* button:this->buttons_)
        delete button;
}

void MainWindow::CreateWindowButton()
{
    // Build start button
    this->buttons_[0]=new MainEntryButton(FilePathSystem::GetInstance().GetResourcesPath(resourcesfiletype::ResourcesType::Image,"start.png"),
                                            QSize((this->width() / 2 - this->width() / 10 * 3), this->height() / 8)
                                            , "开始");
    this->buttons_[0]->move(QPoint((this->width() / 16), (this->height() - this->height() / 4)));

    // Build setup button
    this->buttons_[1] = new MainEntryButton(FilePathSystem::GetInstance().GetResourcesPath(resourcesfiletype::ResourcesType::Image,"setting.png"),
                                            QSize(this->width() / 2 - this->width() / 10 * 3, this->height() / 8)
                                            , "设置");
    this->buttons_[1]->move(QPoint(this->width() / 2 - this->width() / 9, this->height() - this->height() / 4));

    // Build exit button
    this->buttons_[2] = new MainEntryButton(FilePathSystem::GetInstance().GetResourcesPath(resourcesfiletype::ResourcesType::Image,"end.png"),
                                            QSize(this->width() / 2 - this->width() / 10 * 3, this->height() / 8)
                                            , "退出");
    this->buttons_[2]->move(QPoint(this->width() - this->width() / 3.5, this->height() - this->height() / 4));

    for(MainEntryButton *button:this->buttons_)
    {
        button->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);"
                              "border:2px groove gray;border-radius:10px;"
                              "padding:2px 4px;border-style: outset;}"
                              "QPushButton:hover{background-color:rgb(229, 241, 251); "
                              "color: black;}"
                              "QPushButton:pressed{background-color:rgb(204, 228, 247);"
                              "border-style: inset;}");
        button->setFocusPolicy(Qt::NoFocus);
        button->setParent(this);
    }
}

