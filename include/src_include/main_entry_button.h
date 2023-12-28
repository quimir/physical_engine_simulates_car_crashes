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

#ifndef MAIN_ENTRY_BUTTON_H
#define MAIN_ENTRY_BUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QEnterEvent>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>

class MainEntryButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief MainEntryButton Set the button length and width are enlarged by 10% after the mouse enters, and return to the original length and width after the exit
     * @param icon_path Path to the button image
     * @param src_window The button's length and width
     * @param button_text The text to display for the button
     */
    MainEntryButton(const QString icon_path, const QSize original_size, const QString button_text);

    /**
     * @brief enterEvent Override the mouse entry event so that its length and width are increased by 10% when the mouse enters
     * @param event Mouse entry event
     */
    void enterEvent(QEnterEvent* event)override;

    /**
     * @brief leaveEvent Override the mouse departure event so that the length and width of the mouse return to their original size when the mouse leaves
     * @param event Mouse departure event
     */
    void leaveEvent(QEvent* event)override;

private:

    /**
     * @brief AnimateSizeChange Plot the width and length of the button as the mouse enters and leaves
     * @param start_size The overall length and width at the beginning of the painting
     * @param end_size The overall width and length at the end of the painting
     */
    void AnimateSizeChange(const QSize& start_size, const QSize& end_size);

    void SetButtonIcon(const QImage image);

    /**
     * @brief SettingButtonLayout Sets the flush effect between the button icon and the text
     */
    void SetButtonLayout();

private:
    QImage image_;

    /**
     * @brief original_size_ Save the button size
     */
    QSize original_size_;

    /**
     * @brief animation_ Save the button animation so that the animation system doesn't have to re-initialize and cause memory leaks
     */
    QPropertyAnimation* animation_;

public slots:
    /**
     * @brief OnAnimationFinished This slots prevents the button from crashing due to a memory leak during the stop animation.
     * Therefore, we need to use this model to get the button back to its original state immediately but the problem is that the animation time becomes extremely short,
     * so let's keep this function for now until we can figure out a better way
     */
    void OnAnimationFinished();
};

#endif // MAIN_ENTRY_BUTTON_H
