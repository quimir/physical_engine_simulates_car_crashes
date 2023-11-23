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
 * @file       environmentsettingwindow.h
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/21
 * @history
 *****************************************************************************/

#ifndef ENVIRONMENTSETTINGWINDOW_H
#define ENVIRONMENTSETTINGWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

class EnvironmentSettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EnvironmentSettingWindow(QRect window_geometry,QWidget *parent = nullptr);

signals:

};

#endif // ENVIRONMENTSETTINGWINDOW_H
