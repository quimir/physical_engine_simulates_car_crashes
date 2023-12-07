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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QScreen>
#include <QPushButton>
#include <QEasingCurve>
#include <QTimer>
#include <QOpenGLWindow>
#include <QPaintEvent>
#include <QPixmap>
#include <QPalette>

#include "src_include/main_entry_button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CreateWindowButton();

    /**
     * @brief GetScreenWindow Gets the user's screen to set the window size
     */
    void GetScreenWindow();


    int GetScreenWidth()const;
    int GetScreenHeight()const;

protected:
    void closeEvent(QCloseEvent* event)override;
    void paintEvent(QPaintEvent* event)override;

private:
    void SetUIWindow();

private slots:
    void HandleButtonClicked();

private:
    Ui::MainWindow *ui;

    QVector<MainEntryButton*> buttons_;

    /**
     * @brief screen_width_ user screen width
     */
    int screen_width_;

    /**
     * @brief screen_height_ user screen height
     */
    int screen_height_;
};
#endif // MAIN_WINDOW_H
