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
 * @file       settingwindowbutton.cpp
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/21
 * @history
 *****************************************************************************/

#include "src_include/setting_window/settingwindowbutton.h"
#include "src_include/filewirtesystem.h"

SettingWindowButton::SettingWindowButton(const QString icon_path, const QSize original_size, const QString button_text, const QSize icon_size)
{
    if(original_size.isNull()||button_text.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Setting button original size is: %1,button text is: %2")
                                                                .arg(original_size.isNull()?"null":"no null",button_text.isNull()?"null":"no null"));
    }
    this->original_size_=original_size;
    this->setText("");
    this->button_text_=button_text;

    this->icon_path_=icon_path;
    QPixmap pix(this->icon_path_);
    if(pix.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("%1 button image loading error image path: %2")
                                                                .arg(this->button_text_, icon_path_));
    }

    this->setIcon(pix);
    if(icon_size.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("%1 button icon size is null").arg(this->button_text_));
    }
    this->setIconSize(icon_size);
    this->resize(this->original_size_);

    /**
     * Setting the style
    **/
    this->setFlat(true);
    // Setting stylesheets
    this->setStyleSheet("SettingWindowButton {"
                        "    border: none;" // Hide borders
                        "}"
                        "SettingWindowButton:hover {"
                        "    border: none;" // The border is also not displayed when the mouse is hovered
                        "}");
    QFont font("Arial",10);
    this->setFont(font);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    // Install the mouse event listener
    this->installEventFilter(this);

    connect(this,&QPushButton::clicked,this,&SettingWindowButton::ShowPopupWidget);
}

bool SettingWindowButton::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(event);
    if(obj==this)
    {

        if(event->type()==QEvent::Enter)
        {
            QToolTip::setFont(QFont("Arial",10));
            QToolTip::showText(mapToGlobal(rect().bottomRight()),this->button_text_);
        }
        else if(event->type()==QEvent::Leave)
        {
            QToolTip::hideText();
        }
        return QWidget::eventFilter(obj,event);
    }

    return false;
}

void SettingWindowButton::ShowPopupWidget()
{
    emit ButtonClicked();
}
