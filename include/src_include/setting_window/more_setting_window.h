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

#ifndef SETTING_WINDOW_MORE_SETTING_WINDOW_H
#define SETTING_WINDOW_MORE_SETTING_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>

class MoreSettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MoreSettingWindow(QRect window_geometry,QWidget *parent = nullptr);

signals:

};

#endif // SETTING_WINDOWSMORE_SETTING_WINDOW_H

