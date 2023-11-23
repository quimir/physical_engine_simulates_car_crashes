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
 * @file       settingwindowbutton.h
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/21
 * @history
 *****************************************************************************/

#ifndef SETTINGWINDOWBUTTON_H
#define SETTINGWINDOWBUTTON_H

#include <QPushButton>
#include <QToolTip>
#include <QRect>
#include <QPainter>
#include <QPixmap>

class SettingWindowButton : public QPushButton
{
    Q_OBJECT
public:
    SettingWindowButton(const QString icon_path,const QSize original_size,const QString button_text,const QSize icon_size);

protected:
    bool eventFilter(QObject* obj,QEvent* event);

private:
    QString icon_path_;
    QSize original_size_;
    QString button_text_;

signals:
    void ButtonClicked();

private slots:
    void ShowPopupWidget();
};

#endif // SETTINGWINDOWBUTTON_H
