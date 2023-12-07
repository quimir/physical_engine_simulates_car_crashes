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
 * @file       settingwindow.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef SETTING_WINDOW_H
#define SETTING_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "src_include/setting_window/basic_setting_window.h"
#include "src_include/setting_window/more_setting_window.h"
#include "src_include/setting_window/environment_setting_window.h"
#include "src_include/setting_window/setting_window_button.h"

class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWindow(const QRect& window_geometry,QWidget *parent = nullptr);

    void CreateBasicButton(const QSize button_size);

    void CreateEnvironmentButton(const QSize button_size);

    void CreateMoreButton(const QSize button_size);

    void CreateWindowLayout();

    void CreateChildWindow(const QSize button_size);

    void CreateWindowInterface();

    QSize GetButtonSize();

    void CreateRetunButton(const QSize button_size);

    void CreateStartButton(const QSize button_size);

    ~SettingWindow();

protected:
    void closeEvent(QCloseEvent* event)override;
    void paintEvent(QPaintEvent* event)override;

private:
    bool processing_button_click_;

    BasicSettingsWindow* basic_setting_window_;
    MoreSettingWindow* more_setting_window_;
    EnvironmentSettingWindow* enviroment_setting_window_;
    QVector<SettingWindowButton*> setting_left_buttons_;
    QVector<SettingWindowButton*> setting_right_buttons_;

public slots:
    void HandleButtonClicked();

private slots:
    void ReturnToMainWindow();
};

#endif // SETTING_WINDOW_H
