/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       settingbutton.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/31
 * @history
 *****************************************************************************/

#ifndef SETTINGBUTTON_H
#define SETTINGBUTTON_H

#include <QPushButton>
#include <QString>
#include <QEnterEvent>
#include <QFontMetrics>
#include <QPropertyAnimation>
#include <QHBoxLayout>

class SettingButton : public QPushButton
{
public:
    SettingButton(const QString icon_path,const QSize original_size,const QString button_text);

    void enterEvent(QEnterEvent *event)override;

    void leaveEvent(QEvent *event)override;

private:
    void AnimateSizeChange(const QSize &start_size,const QSize& end_size);

    void SetButtonIcon(const QString icon_path);

    void SetButtonLayout();

private:
    QString icon_path_;

    QSize original_size_;

    QPropertyAnimation *animation_;
};

#endif // SETTINGBUTTON_H
