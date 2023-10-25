/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       mainwindow.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/13
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
