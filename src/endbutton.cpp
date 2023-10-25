#include "src_include/endbutton.h"
#include "src_include/filewirtesystem.h"


EndButton::EndButton(const QString icon_path, const QSize src_window)
{
    this->original_size_=src_window;
    this->icon_path_=icon_path;
    QPixmap pix(this->icon_path_);
    if(pix.isNull())
    {
        QString out_string=QString("Image loading error:%1").arg(icon_path_);
        FileWirteSystem::OutMessage(2,out_string);
    }
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()/10,pix.height()/10));
    this->resize(this->original_size_);
}

void EndButton::enterEvent(QEnterEvent *event)
{
    AnimateSizeChange(this->original_size_,QSize(this->original_size_.width()*1.1,this->original_size_.height()*1.1));
    event->accept();
}

void EndButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    AnimateSizeChange(this->size(),this->original_size_);
    QPushButton::leaveEvent(event);
}

void EndButton::AnimateSizeChange(const QSize &start_size, const QSize &end_size)
{
    if(!this->animation_)
    {
        this->animation_=new QPropertyAnimation(this,"geometry");
        this->animation_->setDuration(200);
    }
    FileWirteSystem::OutMessage(1,QString("Button Start Width: %1,Height: %2").arg(QString::number(start_size.width()),
                                                                                    QString::number(start_size.height()))
                                       +QString("Button End Width: %1,Height: %2").arg(QString::number(end_size.width()),
                                                                                        QString::number(end_size.height())));

    this->animation_->stop();
    this->animation_->setStartValue(QRect(this->pos(),start_size));
    this->animation_->setEndValue(QRect(this->pos(),end_size));
    this->animation_->setEasingCurve(QEasingCurve::InOutQuad);
    this->animation_->start();
}
