#include "src_include/settingwindow.h"
#include "src_include/filewirtesystem.h"

SettingWindow::SettingWindow(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("汽车仿真碰撞引擎");
    QPushButton *basic_button=SetBasicButton();
    basic_button->setParent(this);
    basic_button->installEventFilter(this);
}

QPushButton* SettingWindow::SetBasicButton()
{
    QPushButton* basic_button=new QPushButton("基本设置");
    basic_button->move(QPoint(this->width()/10,0));
    basic_button->resize(QSize(this->width()/20,this->height()/4));
    FileWirteSystem::OutMessage("debug",QString("basic_button width: %1,height: %2").arg(QString::number(basic_button->width()),QString::number(basic_button->height())));
    basic_button->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:4px;padding:2px 4px;border-style: outset;}"
                                "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    return basic_button;
}
