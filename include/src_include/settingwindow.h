/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       settingwindow.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/26
 * @history
 *****************************************************************************/


#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWindow(QWidget *parent = nullptr);

    QPushButton* SetBasicButton();

    QPushButton* SetEnvironmentButton();

    QPushButton* SetMoreButton();

    QPushButton* SetRetunButton();

    QPushButton* SetStartButton();

signals:
    void ShowSettingWindow();
};

#endif // SETTINGWINDOW_H
