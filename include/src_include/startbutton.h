/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       startbutton.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/13
 * @history
 *****************************************************************************/

#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QtGlobal>
#include <QEnterEvent>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>

class StartButton : public QPushButton
{
public:
    StartButton(const QString icon_path,const QSize src_window,const QString button_text);

    void enterEvent(QEnterEvent *event)override;
    void leaveEvent(QEvent *event)override;

    ~StartButton();

private:
    void AnimateSizeChange(const QSize&start_size,const QSize&end_size);
    void SettingButtonIcon(const QString icon_path);
    void SettingButtonLayout();

private:
    QString icon_path_;
    QSize original_size_;
    QPropertyAnimation *animation_;
};

#endif // STARTBUTTON_H
