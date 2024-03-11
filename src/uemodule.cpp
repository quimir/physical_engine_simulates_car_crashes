#include "src_include/uemodule.h""

UEModule::UEModule(QWidget *parent)
    : QWidget{parent},process_(nullptr),ue_window_(nullptr),window_widget_(parent),timer_(nullptr)
{
    InitWidget();
}

void UEModule::InitWidget()
{
    this->timer_=new QTimer(this);
    connect(this->timer_,&QTimer::timeout,this,&UEModule::TimerShowUe);
    this->timer_->start(10);

    connect(this,&UEModule::SignalsUeComplete,this,&UEModule::SlotUeComplete);
}

void UEModule::TimerShowUe()
{
    if(this->window_widget_)
    {
        if(GetForegroundWindow()!=this->ue_window_ && !this->isActiveWindow())
        {
            SetWindowPos(this->ue_window_,HWND_NOTOPMOST,mapToGlobal(this->window_widget_->pos()).x(),
                         mapToGlobal(this->window_widget_->pos()).y(),this->window_widget_->width(),
                         this->window_widget_->height(),SWP_NOACTIVATE);
        }
    }
}

void UEModule::KillProcessByName(const QString &process_name)
{
    QProcess process;
    process.start("tasklist",QStringList()<<"/fo"<<"csv"<<"/nh");
    process.waitForStarted();
    QString output=process.readAllStandardOutput();

    QStringList lines=output.split("\n");
    for(QString& line:lines)
    {
        QStringList fields=line.split(",");
        if(fields.count()<2)
        {
            continue;
        }

        QString pid=fields[1].trimmed().replace("\"","");
        QString name=fields[0].trimmed().replace("\"","");

        if(name==process_name)
        {
            QProcess::execute("taskkill",QStringList()<<"/F"<<"/PID"<<pid);
        }
    }
}
