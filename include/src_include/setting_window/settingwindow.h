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

#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "src_include/setting_window/basicsettingswindow.h"
#include "src_include/setting_window/moresettingwindow.h"
#include "src_include/setting_window/environmentsettingwindow.h"
#include "src_include/setting_window/settingwindowbutton.h"

class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWindow(const QRect& window_geometry,QWidget *parent = nullptr);

    void SetBasicButton(const QSize button_size);

    void SetEnvironmentButton(const QSize button_size);

    void SetMoreButton(const QSize button_size);

    void SetWindowLayout();

    void SetChildWindow(const QSize button_size);

    void SetWindow();

    QSize GetButtonSize();

    QPushButton* SetRetunButton();

    QPushButton* SetStartButton();

protected:
    void closeEvent(QCloseEvent* event)override;

private:
    bool processing_button_click_;

    BasicSettingsWindow* basic_setting_window_;
    MoreSettingWindow* more_setting_window_;
    EnvironmentSettingWindow* enviroment_setting_window_;
    QVector<SettingWindowButton*> setting_buttons_;

public slots:
    void HandleButtonClicked();

private slots:
    void ReturnToMainWindow();
};

#endif // SETTINGWINDOW_H
