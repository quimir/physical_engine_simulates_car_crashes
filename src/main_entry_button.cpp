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

#include "src_include/main_entry_button.h"
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/file_read_system.h"

/**
 * @brief KTextAndIconSpacing Button text and icon spacing
 */
constexpr int KTextAndIconSpacing = 5;

MainEntryButton::MainEntryButton(const QString icon_path, const QSize original_size, const QString button_text):
    image_(FileReadSystem::GetInstance().ReadImageFile(icon_path)),original_size_(original_size)
{
    if(this->original_size_.isEmpty()||button_text.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug
            ,QString("Setting button original size is: %1,button text is: %2")
                .arg(original_size.isNull()?"null":"no null",
                     button_text.isNull()?"null":"no null"));
    }

    this->setText(button_text);
    SetButtonIcon(this->image_);

    this->animation_ = new QPropertyAnimation(this, "geometry");
    this->animation_->setDuration(400);

    connect(this->animation_, &QObject::destroyed, this, [=]() {
        if (this->animation_ && this->animation_->state() == QPropertyAnimation::Running)
            this->animation_->stop();
    });

    this->resize(this->original_size_);

    //    // Connect the finished signal to onAnimationFinished slot
    //    connect(this->animation_, &QPropertyAnimation::finished, this, &MainEntryButton::OnAnimationFinished);
}

void MainEntryButton::enterEvent(QEnterEvent* event)
{
    AnimateSizeChange(original_size_, QSize(original_size_.width() * 1.1,
                                            original_size_.height() * 1.1));
    event->accept();
}

void MainEntryButton::leaveEvent(QEvent* event)
{
    Q_UNUSED(event);
    AnimateSizeChange(this->size(), original_size_);
    QPushButton::leaveEvent(event);
}


void MainEntryButton::AnimateSizeChange(const QSize& start_size,
                                        const QSize& end_size)
{
    this->animation_->setStartValue(QRect(this->pos(), start_size));
    this->animation_->setEndValue(QRect(this->pos(), end_size));
    this->animation_->setEasingCurve(QEasingCurve::InOutQuad);
    this->animation_->start();
}

void MainEntryButton::SetButtonIcon(const QImage image)
{
    QPixmap pix=QPixmap::fromImage(image);
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
    QLayout *existing_layout = layout();
    if (existing_layout)
    {
        delete existing_layout;
    }

    // Create a new widget to hold the button
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(KTextAndIconSpacing);

    if (!this->icon().isNull())
    {
        layout->addWidget(this);
        layout->addSpacing(KTextAndIconSpacing);
    }

    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void MainEntryButton::OnAnimationFinished()
{
    this->resize(this->original_size_);
}
