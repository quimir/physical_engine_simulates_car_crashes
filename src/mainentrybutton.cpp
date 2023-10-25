#include "src_include/mainentrybutton.h"
#include "src_include/filewirtesystem.h"

/**
 * @brief TEXTANDICONSPACING Button text and icon spacing
 */
constexpr int TEXTANDICONSPACING=5;

MainEntryButton::MainEntryButton(const QString icon_path, const QSize original_size,const QString button_text)
{
    this->original_size_=original_size;
    this->setText(button_text);
    SetButtonIcon(icon_path);

    this->animation_=new QPropertyAnimation(this,"geometry");
    this->animation_->setDuration(400);

    connect(this->animation_,&QObject::destroyed,this,[=](){
        if(this->animation_&&this->animation_->state()==QPropertyAnimation::Running)
            this->animation_->stop();
    });

    this->resize(this->original_size_);

    // Connect the finished signal to onAnimationFinished slot
    connect(this->animation_,&QPropertyAnimation::finished,this,&MainEntryButton::OnAnimationFinished);
}

void MainEntryButton::enterEvent(QEnterEvent *event)
{
    FileWirteSystem::OutMessage(1,QString("Mouse entered button: %1").arg(this->text()));
    AnimateSizeChange(original_size_,QSize(original_size_.width()*1.1,original_size_.height()*1.1));
    event->accept();
}

void MainEntryButton::leaveEvent(QEvent *event)
{
    FileWirteSystem::OutMessage(1,QString("Mouse leave button: %1").arg(this->text()));
    Q_UNUSED(event);
    AnimateSizeChange(this->size(),original_size_);
    QPushButton::leaveEvent(event);
}


void MainEntryButton::AnimateSizeChange(const QSize &start_size, const QSize &end_size)
{
    FileWirteSystem::OutMessage(1,QString("%1 ").arg(this->text())+
                                QString("button start width: %1,height: %2").arg(QString::number(start_size.width()),
                                                                                    QString::number(start_size.height()))
                                +QString(" button end width: %1,height: %2").arg(QString::number(end_size.width()),
                                                                                QString::number(end_size.height())));
    this->animation_->setStartValue(QRect(this->pos(),start_size));
    this->animation_->setEndValue(QRect(this->pos(),end_size));
    this->animation_->setEasingCurve(QEasingCurve::InOutQuad);
    FileWirteSystem::OutMessage(1,QString("exit button animation: %1").arg(this->text()));
    this->animation_->start();
}

void MainEntryButton::SetButtonIcon(const QString icon_path)
{
    this->icon_path_=icon_path;
    QPixmap pix(this->icon_path_);
    if(pix.isNull())
    {
        FileWirteSystem::OutMessage(1,QString("%1 button image loading error image path: %2")
                                           .arg(this->text(),icon_path_));
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

void MainEntryButton::OnAnimationFinished()
{
    this->resize(this->original_size_);
}
