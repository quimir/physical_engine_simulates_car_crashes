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
 * @file       mainwindow.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QScreen>
#include <QPushButton>
#include <QEasingCurve>
#include <QTimer>
#include <QOpenGLWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief PlaceStartButton This function is used to place the start button on the UI
     */
    void PlaceStartButton();

    /**
     * @brief PlaceEndButton This function is used to place the end button on the UI
     */
    void PlaceEndButton();

    /**
     * @brief PlaceSettingButton This function is used to place the setting button on the UI
     */
    void PlaceSettingButton();
    void GetScreenWindow();
    int GetScreenWidth()const;
    int GetScreenHeight()const;

protected:
    void closeEvent(QCloseEvent* event)override;

private:
    void SetUIWindow();
    Ui::MainWindow *ui;

    /**
     * @brief screen_width_ user screen width
     */
    int screen_width_;

    /**
     * @brief screen_height_ user screen height
     */
    int screen_height_;
};
#endif // MAINWINDOW_H
