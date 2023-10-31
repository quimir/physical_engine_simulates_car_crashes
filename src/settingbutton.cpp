#include "src_include/settingbutton.h"
#include "src_include/filewirtesystem.h"

/**
 * @brief TEXTANDICONSPACING Button text and icon spacing
 */
constexpr int TEXTANDICONSPACING = 5;

SettingButton::SettingButton(const QString icon_path, const QSize original_size, const QString button_text)
{
    if(original_size.isNull()||button_text.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Setting button original size is: %1,button text is: %2")
                                    .arg(original_size.isNull()?"null":"no null",button_text.isNull()?"null":"no null"));
    }

    this->original_size_=original_size;
    this->setText(button_text);
    SetButtonIcon(icon_path);
}

void SettingButton::enterEvent(QEnterEvent *event)
{

}

void SettingButton::leaveEvent(QEvent *event)
{

}

void SettingButton::AnimateSizeChange(const QSize &start_size, const QSize &end_size)
{

}

void SettingButton::SetButtonIcon(const QString icon_path)
{
    this->icon_path_=icon_path;
    QPixmap pix(this->icon_path_);
    if(pix.isNull())
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

void SettingButton::SetButtonLayout()
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
