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

SettingWindow::SettingWindow(QWidget *parent)
    : QWidget{parent},processing_button_click_(false)
{
    this->setWindowTitle("汽车仿真碰撞引擎");
    QPushButton *basic_button=SetBasicButton();
    basic_button->setParent(this);
    basic_button->installEventFilter(this);

    for(SettingWindowButton* button:this->setting_buttons_)
    {
        connect(button,&SettingWindowButton::clicked,this,&SettingWindow::HandleButtonClicked);
    }
}

QPushButton* SettingWindow::SetBasicButton()
{
    QPushButton* basic_button=new QPushButton("基本设置");
    basic_button->move(QPoint(this->width()/10,0));
    basic_button->resize(QSize(this->width()/20,this->height()/4));
    FileWirteSystem::OutMessage("debug",QString("basic_button width: %1,height: %2").arg(QString::number(basic_button->width()),QString::number(basic_button->height())));
    basic_button->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:4px;padding:2px 4px;border-style: outset;}"
                                "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    return basic_button;
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
    else if(this->weather_setting_window_->isVisible())
    {
        this->weather_setting_window_->close();
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
        this->weather_setting_window_->show();
    }

    // The click event has been processed
    this->processing_button_click_=false;
}
