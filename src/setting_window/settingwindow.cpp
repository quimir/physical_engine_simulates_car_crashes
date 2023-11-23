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
 * @file       settingwindow.cpp
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#include "src_include/setting_window/settingwindow.h"
#include "src_include/filewirtesystem.h"
#include "src_include/filepathsystem.h"
#include "src_include/mainwindow.h"

SettingWindow::SettingWindow(const QRect &window_geometry, QWidget *parent)
    : QWidget{parent},processing_button_click_(false)
{
    this->setGeometry(window_geometry);
    this->setWindowTitle("汽车仿真碰撞引擎");

    SetWindow();

    for(SettingWindowButton* button:this->setting_buttons_)
    {
        connect(button,&SettingWindowButton::clicked,this,&SettingWindow::HandleButtonClicked);
    }
}

void SettingWindow::SetBasicButton(const QSize button_size)
{
    SettingWindowButton* basic_button=new SettingWindowButton(FilePathSystem::GetImagePath("setting_start.png")
                                                                ,button_size*2+button_size/3,"基本设置",button_size*2);
    if(nullptr==basic_button)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Failed to create the %1 button").arg("基本设置"));
    }
    basic_button->move(button_size.width()/2,button_size.height()/2);
    basic_button->setParent(this);
    this->setting_buttons_.push_back(basic_button);
}

void SettingWindow::SetEnvironmentButton(const QSize button_size)
{
    SettingWindowButton* enviroment_button=new SettingWindowButton(FilePathSystem::GetImagePath("setting_weath.png")
                                                                     ,button_size*2+button_size/3,"环境设置",button_size*2);
    if(nullptr==enviroment_button)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Failed to create the %1 button").arg("环境设置"));
    }
    enviroment_button->move(button_size.width()/2,button_size.height()*6+button_size.height()/2);
    enviroment_button->setParent(this);
    this->setting_buttons_.push_back(enviroment_button);
}

void SettingWindow::SetMoreButton(const QSize button_size)
{
    SettingWindowButton* more_button=new SettingWindowButton(FilePathSystem::GetImagePath("setting_more.png")
                                                               ,button_size*2+button_size/3,"更多设置",button_size*2);
    if(nullptr==more_button)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Failed to create the %1 button").arg("更多设置"));
    }
    more_button->move(button_size.width()/2,button_size.height()*3+button_size.height()/2);
    more_button->setParent(this);
    this->setting_buttons_.push_back(more_button);
}

void SettingWindow::SetWindowLayout()
{
    // Create a vertical layout style
    QVBoxLayout* buttons_layout=new QVBoxLayout;
    if(nullptr==buttons_layout)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Warning,"No buttons layout created");
    }

    // Put all the buttons in a vertical layout
    for(SettingWindowButton* button:this->setting_buttons_)
    {
        buttons_layout->addWidget(button);
    }

    // Create a horizontal layout style so that the child window is on the same line as the button
    QHBoxLayout* main_layout=new QHBoxLayout(this);
    main_layout->addLayout(buttons_layout);
    main_layout->addWidget(this->basic_setting_window_);
    main_layout->addWidget(this->more_setting_window_);
    main_layout->addWidget(this->enviroment_setting_window_);
    this->setLayout(main_layout);
    this->basic_setting_window_->show();
    this->more_setting_window_->close();
    this->enviroment_setting_window_->close();
}

void SettingWindow::SetChildWindow(const QSize button_size)
{
    QRect child_window_geometry=QRect(button_size.width() * 2 + button_size.width() / 3 + button_size.width() / 2,
                                        button_size.height() / 2,
                                        (this->width() - (button_size.width() * 2 + button_size.width() / 3 + button_size.width() / 2)),
                                        this->height() - button_size.height());

    this->basic_setting_window_=new BasicSettingsWindow(child_window_geometry,this);
    if(nullptr==this->basic_setting_window_)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Warning,"The basic setting window failed to create");
    }

    this->more_setting_window_=new MoreSettingWindow(child_window_geometry,this);
    if(nullptr==this->more_setting_window_)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Warning,"The more setting window failed to create");
    }

    this->enviroment_setting_window_=new EnvironmentSettingWindow(child_window_geometry,this);
    if(nullptr==this->enviroment_setting_window_)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Warning,"The environment setting window failed to create");
    }
}

void SettingWindow::SetWindow()
{
    QSize button_size=GetButtonSize();
    SetBasicButton(button_size);
    SetMoreButton(button_size);
    SetEnvironmentButton(button_size);
    SetChildWindow(button_size);
    SetWindowLayout();
}

QSize SettingWindow::GetButtonSize()
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Setting window width: %1 height: %2")
                                                            .arg(QString::number(this->width()),QString::number(this->height())));
    const qint32 edge_distance_width=this->size().width()/100*10;
    const qint32 edge_distance_height=this->size().height()/100*10;
    FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Button edge distance width: %1 height: %2")
                                                            .arg(QString::number(edge_distance_width),QString::number(edge_distance_height)));
    QSize button_size(edge_distance_width,edge_distance_height);
    return button_size;
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug,"The user closes the window using the close event in the upper-right corner");
    FileWirteSystem::EndWirteLine();
}

void SettingWindow::HandleButtonClicked()
{
    // Ensure that the same click event is not triggered twice
    if(this->processing_button_click_)
        return;

    SettingWindowButton* clicked_button=qobject_cast<SettingWindowButton*>(sender());
    if(nullptr==clicked_button)
        return;

    // Handle click event wait
    this->processing_button_click_=true;

    // Close the current subwindow
    if(this->basic_setting_window_->isVisible())
    {
        this->basic_setting_window_->close();
    }
    else if(this->more_setting_window_->isVisible())
    {
        this->more_setting_window_->close();
    }
    else if(this->enviroment_setting_window_->isVisible())
    {
        this->enviroment_setting_window_->close();
    }

    // show the current subwindow
    if(clicked_button==this->setting_buttons_[0])
    {
        this->basic_setting_window_->show();
    }
    else if(clicked_button==this->setting_buttons_[1])
    {
        this->more_setting_window_->show();
    }
    else if(clicked_button==this->setting_buttons_[2])
    {
        this->enviroment_setting_window_->show();
    }

    // The click event has been processed
    this->processing_button_click_=false;
}

void SettingWindow::ReturnToMainWindow()
{
    MainWindow* main_window=new MainWindow();
    if(main_window)
    {
        main_window->show();
        this->close();
    }
}
