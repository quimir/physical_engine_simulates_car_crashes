/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2023 QuiMir <2546670299@qq.com>.
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 ** http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 **/

#include "src_include/setting_window/setting_window_button.h"
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/file_read_system.h"

SettingWindowButton::SettingWindowButton(const QString icon_path, const QSize original_size
                                         , const QString button_text, const QSize icon_size, const QString specify_the_display_text, const QString press_icon_path)
    :icon_image_(FileReadSystem::GetInstance().ReadImageFile(icon_path)),press_icon_image_(FileReadSystem::GetInstance().ReadImageFile(icon_path)),specify_the_display_text_(specify_the_display_text)
{
    if(original_size.isNull()||button_text.isNull())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,QString("Setting button original size is: %1,button text is: %2")
                                                      .arg(original_size.isNull()?"null":"no null",button_text.isNull()?"null":"no null"));
        return;
    }
    this->original_size_=original_size;
    this->setText("");
    this->button_text_=button_text;

    if(this->icon_image_.isNull())
    {
        return;
    }

    QPixmap pix=QPixmap::fromImage(this->icon_image_);
    this->setIcon(pix);
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

void SettingWindowButton::mousePressEvent(QMouseEvent *event)
{
    if(!this->press_icon_image_.isNull())
    {
        if(this->specify_the_display_text_.compare("setting start",Qt::CaseInsensitive))
        {
            QPixmap pix=QPixmap::fromImage(this->press_icon_image_);
            this->setIcon(pix);
            this->setIconSize(this->original_size_);
        }
    }
    QPushButton::mousePressEvent(event);
}

void SettingWindowButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(!this->icon_image_.isNull())
    {
        if(this->specify_the_display_text_.compare("setting start",Qt::CaseInsensitive))
        {
            QPixmap pix=QPixmap::fromImage(this->icon_image_);
            this->setIcon(pix);
            this->setIconSize(this->original_size_);
        }
    }
    QPushButton::mouseReleaseEvent(event);
}

void SettingWindowButton::ShowPopupWidget()
{
    emit ButtonClicked();
}
