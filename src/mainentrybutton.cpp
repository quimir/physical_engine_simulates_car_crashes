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
 * @file       mainentrybutton.cpp
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#include "src_include/mainentrybutton.h"
#include "src_include/filewirtesystem.h"

/**
 * @brief TEXTANDICONSPACING Button text and icon spacing
 */
constexpr int TEXTANDICONSPACING = 5;

MainEntryButton::MainEntryButton(const QString icon_path, const QSize original_size, const QString button_text)
{
    if(original_size.isNull()||button_text.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Setting button original size is: %1,button text is: %2")
                                           .arg(original_size.isNull()?"null":"no null",button_text.isNull()?"null":"no null"));
    }

    this->original_size_ = original_size;
    this->setText(button_text);
    SetButtonIcon(icon_path);

    this->animation_ = new QPropertyAnimation(this, "geometry");
    this->animation_->setDuration(400);

    connect(this->animation_, &QObject::destroyed, this, [=]() {
        if (this->animation_ && this->animation_->state() == QPropertyAnimation::Running)
            this->animation_->stop();
    });

    this->resize(this->original_size_);

    // Connect the finished signal to onAnimationFinished slot
    connect(this->animation_, &QPropertyAnimation::finished, this, &MainEntryButton::OnAnimationFinished);
}

void MainEntryButton::enterEvent(QEnterEvent* event)
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("Mouse entered button: %1").arg(this->text()));
    AnimateSizeChange(original_size_, QSize(original_size_.width() * 1.1, original_size_.height() * 1.1));
    event->accept();
}

void MainEntryButton::leaveEvent(QEvent* event)
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("Mouse leave button: %1").arg(this->text()));
    Q_UNUSED(event);
    AnimateSizeChange(this->size(), original_size_);
    QPushButton::leaveEvent(event);
}


void MainEntryButton::AnimateSizeChange(const QSize& start_size, const QSize& end_size)
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("%1 ").arg(this->text()) +
                                       QString("button start width: %1,height: %2").arg(QString::number(start_size.width()),
                                                                                        QString::number(start_size.height()))
                                       + QString(" button end width: %1,height: %2").arg(QString::number(end_size.width()),
                                                                                         QString::number(end_size.height())));
    this->animation_->setStartValue(QRect(this->pos(), start_size));
    this->animation_->setEndValue(QRect(this->pos(), end_size));
    this->animation_->setEasingCurve(QEasingCurve::InOutQuad);
    FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("exit button animation: %1").arg(this->text()));
    this->animation_->start();
}

void MainEntryButton::SetButtonIcon(const QString icon_path)
{
    this->icon_path_ = icon_path;
    QPixmap pix(this->icon_path_);
    if (pix.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug, QString("%1 button image loading error image path: %2")
                                           .arg(this->text(), icon_path_));
    }
    this->setIcon(pix);

    // Get font metrics
    QFontMetrics font_metrices(this->font());
    int text_width = font_metrices.horizontalAdvance(this->text());// Button text width
    int text_height = font_metrices.height();// Button text height

    int icon_size = qMax(text_height, text_width);
    this->setIconSize(QSize(icon_size, icon_size));
    this->setMinimumHeight(icon_size);
    this->setStyleSheet("text-align:left;");

    SetButtonLayout();
}

void MainEntryButton::SetButtonLayout()
{
    // Remove old layout objects to avoid memory leaks
    QLayout* existingLayout = layout();
    if (existingLayout) {
        delete existingLayout;
    }

    // Create a new widget to hold the button
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(TEXTANDICONSPACING);

    if (!this->icon().isNull())
    {
        layout->addWidget(this);
        layout->addSpacing(TEXTANDICONSPACING);
    }

    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void MainEntryButton::OnAnimationFinished()
{
    this->resize(this->original_size_);
}
