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

#include "src_include/setting_window/more_setting_window.h"
#include "src_include/file_system/file_write_system.h"

MoreSettingWindow::MoreSettingWindow(QRect window_geometry, QWidget *parent)
    : QWidget{parent}
{
    this->setGeometry(window_geometry);
    QVBoxLayout* layout=new QVBoxLayout(this);
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug,QString("more setting window width: %1,height: %2")
                                                            .arg(QString::number(this->width()),QString::number(this->height())));

    for(quint32 i=0;i<20;i++)
    {
        QLabel* label=new QLabel(QString("更多测试: %1").arg(QString::number(i+1)));
        layout->addWidget(label);
    }

    QScrollArea* scroll_area=new QScrollArea(this);

    QWidget* scroll_widget=new QWidget();
    scroll_widget->setLayout(layout);

    scroll_area->setWidget(scroll_widget);

    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QVBoxLayout* main_layout=new QVBoxLayout(this);
    main_layout->addWidget(scroll_area);
}
