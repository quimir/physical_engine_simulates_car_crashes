#include "src_include/startbutton.h"
#include "src_include/filewirtesystem.h"

constexpr int TEXTANDICONSPACING=5;

StartButton::StartButton(const QString icon_path, const QSize src_window, const QString button_text)
{
    this->original_size_=src_window;
    this->setText(button_text);
    SettingButtonIcon(icon_path);
    this->resize(this->original_size_);
}

void StartButton::enterEvent(QEnterEvent *event)
{
    AnimateSizeChange(original_size_,QSize(original_size_.width()*1.1,original_size_.height()*1.1));
    event->accept();
}

void StartButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    AnimateSizeChange(this->size(),original_size_);
    QPushButton::leaveEvent(event);
}

StartButton::~StartButton()
{
    if(this->animation_)
    {
        animation_->stop();
        delete this->animation_;
    }
}

void StartButton::AnimateSizeChange(const QSize &start_size, const QSize &end_size)
{
    if(!this->animation_)
    {
        this->animation_=new QPropertyAnimation(this,"geometry");
        this->animation_->setDuration(200);
    }
    FileWirteSystem::OutMessage(1,QString("%1 ").arg(this->text())+
                                       QString("button Start Width: %1,Height: %2").arg(QString::number(start_size.width()),
                                                                                        QString::number(start_size.height()))
                                       +QString(" button End Width: %1,Height: %2").arg(QString::number(end_size.width()),
                                                                                         QString::number(end_size.height())));

    this->animation_->stop();
    this->animation_->setStartValue(QRect(this->pos(),start_size));
    this->animation_->setEndValue(QRect(this->pos(),end_size));
    this->animation_->setEasingCurve(QEasingCurve::InOutQuad);
    this->animation_->start();
}

void StartButton::SettingButtonIcon(const QString icon_path)
{
    this->icon_path_=icon_path;
    QPixmap pix(this->icon_path_);
    if(pix.isNull())
    {
        FileWirteSystem::OutMessage(1,QString("%1 button image loading error image path: %2").arg(this->text(),icon_path_));
    }
    this->setIcon(pix);

    // Get font metrics
    QFontMetrics font_metrices(this->font());
    int text_width=font_metrices.horizontalAdvance(this->text());// Button text width
    int text_height=font_metrices.height();// Button text height

    int icon_size=qMax(text_height,text_width);
    this->setIconSize(QSize(icon_size,icon_size));
    this->setMinimumHeight(icon_size);
    this->setStyleSheet("text-align:left;");

    SettingButtonLayout();
}

void StartButton::SettingButtonLayout()
{
    // Remove old layout objects to avoid memory leaks
    QLayout* existingLayout = layout();
    if (existingLayout) {
        delete existingLayout;
    }

    // Create a new widget to hold the button
    QHBoxLayout *layout=new QHBoxLayout(this);
    layout->setSpacing(TEXTANDICONSPACING);

    if(!this->icon().isNull())
    {
        layout->addWidget(this);
        layout->addSpacing(TEXTANDICONSPACING);
    }

    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
}
