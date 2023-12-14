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
 * @file       setting_window_button.h
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/21
 * @history
 *****************************************************************************/

#ifndef SETTING_WINDOW_SETTING_WINDOW_BUTTON_H
#define SETTING_WINDOW_SETTING_WINDOW_BUTTON_H

#include <QPushButton>
#include <QToolTip>
#include <QRect>
#include <QPainter>
#include <QPixmap>
#include <QImageReader>

class SettingWindowButton : public QPushButton
{
    Q_OBJECT
public:
    SettingWindowButton(const QString icon_path,const QSize original_size
                        ,const QString button_text,const QSize icon_size,const QString specify_the_display_text=QString()
                        ,const QString press_icon_path=QString());

protected:
    bool eventFilter(QObject* obj,QEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QString icon_path_;
    QString press_icon_path_;
    QSize original_size_;
    QString button_text_;
    QString specify_the_display_text_;

signals:
    void ButtonClicked();

private slots:
    void ShowPopupWidget();
};

#endif // SETTING_WINDOW_SETTING_WINDOW_BUTTON_H
