/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       endbutton.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/10/13
 * @history
 *****************************************************************************/

#ifndef ENDBUTTON_H
#define ENDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QEnterEvent>

class EndButton : public QPushButton
{
public:
    EndButton(const QString icon_path, const QSize src_window);

    void enterEvent(QEnterEvent*event)override;
    void leaveEvent(QEvent*event)override;

private:
    void AnimateSizeChange(const QSize&start_size,const QSize&end_size);

private:
    QString icon_path_;
    QSize original_size_;
    QPropertyAnimation *animation_;
};

#endif // ENDBUTTON_H
