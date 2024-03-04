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

#include "src_include/setting_window/setting_window.h"
#include "qtimer.h"
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/file_path_system.h"
#include "src_include/main_window.h"
#include "src_include/file_system/file_read_system.h"
#include <QResource>

SettingWindow::SettingWindow(const QRect &window_geometry, QWidget *parent)
    : QWidget{parent},processing_button_click_(false)
{
    this->setWindowTitle("汽车仿真碰撞引擎");
    this->setGeometry(window_geometry);

    CreateWindowInterface();

    for(SettingWindowButton* button:this->setting_left_buttons_)
    {
        connect(button,&SettingWindowButton::clicked,this,&SettingWindow::HandleButtonClicked);
    }
}

void SettingWindow::CreateBasicButton(const QSize button_size)
{
    SettingWindowButton* basic_button=new SettingWindowButton(
        FilePathSystem::GetInstance().GetResourcesPath(
            resourcesfiletype::ResourcesType::kImages,
            "setting_cartonn_start.png"),
        button_size*2,"基本设置",button_size*2,"setting basic");
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug,
        "Setting basic button width:"+QString::number(basic_button->width()));
    if(nullptr==basic_button)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            QString("Failed to create the %1 button").arg("setting basic"));
    }

    basic_button->move(button_size.width()/2,button_size.height()/2);
    basic_button->setParent(this);
    this->setting_left_buttons_.push_back(basic_button);
}

void SettingWindow::CreateEnvironmentButton(const QSize button_size)
{
    SettingWindowButton* enviroment_button=new SettingWindowButton(
        FilePathSystem::GetInstance().GetResourcesPath(
            resourcesfiletype::ResourcesType::kImages,"setting_cartonn_weath.png")
        ,button_size*2,"环境设置",button_size*2,"setting weath");
    if(nullptr==enviroment_button)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            QString("Failed to create the %1 button").arg("setting weath"));
    }

    enviroment_button->move(button_size.width()/2,
                            button_size.height()*6+button_size.height()/2);
    enviroment_button->setParent(this);
    this->setting_left_buttons_.push_back(enviroment_button);
}

void SettingWindow::CreateMoreButton(const QSize button_size)
{
    SettingWindowButton* more_button=new SettingWindowButton(
        FilePathSystem::GetInstance().GetResourcesPath(
            resourcesfiletype::ResourcesType::kImages,"setting_cartonn_more.png")
        ,button_size*2,"更多设置",button_size*2,"setting more");
    if(nullptr==more_button)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            QString("Failed to create the %1 button").arg("setting more"));
    }

    more_button->move(button_size.width()/2,
                      button_size.height()*3+button_size.height()/2);
    more_button->setParent(this);
    this->setting_left_buttons_.push_back(more_button);
}

void SettingWindow::CreateWindowLayout()
{
    // Create a vertical layout style
    QVBoxLayout* left_buttons_layout=new QVBoxLayout;
    QVBoxLayout* right_buttons_layout=new QVBoxLayout;
    if(nullptr==left_buttons_layout)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kWarning,
            "No left buttons layout created");
    }
    if(nullptr==right_buttons_layout)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kWarning,
            "No right buttons layout created");
    }

    // Put all the buttons in a vertical layout
    for(SettingWindowButton* left_buttons:this->setting_left_buttons_)
    {
        left_buttons_layout->addWidget(left_buttons);
    }

    for(SettingWindowButton* right_buttons:this->setting_right_buttons_)
    {
        right_buttons_layout->addWidget(right_buttons);
    }

    // Create a horizontal layout style so that the child window is
    // on the same line as the button
    QHBoxLayout* main_layout=new QHBoxLayout(this);
    if(nullptr==main_layout)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kWarning,"No main layout created");
    }

    main_layout->addLayout(left_buttons_layout);
    main_layout->addWidget(this->basic_setting_window_);
    main_layout->addWidget(this->more_setting_window_);
    main_layout->addWidget(this->enviroment_setting_window_);
    main_layout->addLayout(right_buttons_layout);
    // Set layout margins
    main_layout->setContentsMargins(0, 0, 0, 0);

    // Only the first subwindow is displayed when you enter
    this->setLayout(main_layout);
    this->basic_setting_window_->show();
    this->more_setting_window_->close();
    this->enviroment_setting_window_->close();
    
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug
        ,"Left buttons layout width: "
            +QString::number(left_buttons_layout->geometry().width()));
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug,
        "Right buttons layout width: "
            +QString::number(right_buttons_layout->geometry().width()));
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug
        ,"Main layout width: "
            +QString::number(main_layout->geometry().width()));
}

void SettingWindow::CreateChildWindow(const QSize button_size)
{
    QRect child_window_geometry=QRect(button_size.width() * 2,this->height(),
                                        this->width() - (button_size.width()*2),
                                        this->height() - button_size.height());
    
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug,
        "Setting child window width: "
            +QString::number(child_window_geometry.width()));

    this->basic_setting_window_=new BasicSettingsWindow(child_window_geometry,this);
    if(nullptr==this->basic_setting_window_)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kWarning,
            "The basic setting window failed to create");
    }
    this->basic_setting_window_->setWindowTitle("基本设置");

    this->more_setting_window_=new MoreSettingWindow(child_window_geometry,this);
    if(nullptr==this->more_setting_window_)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kWarning,
            "The more setting window failed to create");
    }
    this->more_setting_window_->setWindowTitle("更多设置");

    this->enviroment_setting_window_=new EnvironmentSettingWindow(
        child_window_geometry,this);
    if(nullptr==this->enviroment_setting_window_)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kWarning,
            "The environment setting window failed to create");
    }
    this->enviroment_setting_window_->setWindowTitle("环境设置");
}

void SettingWindow::CreateWindowInterface()
{
    QSize button_size=GetButtonSize();
    CreateBasicButton(button_size);
    CreateMoreButton(button_size);
    CreateEnvironmentButton(button_size);
    CreateRetunButton(button_size);
    CreateStartButton(button_size);
    CreateChildWindow(button_size);
    CreateWindowLayout();
}

QSize SettingWindow::GetButtonSize()
{
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug,
        QString("Setting window width: %1 height: %2")
            .arg(QString::number(this->width()),QString::number(this->height())));
    const qint32 edge_distance_width=this->size().width()/100*10;
    const qint32 edge_distance_height=this->size().height()/100*10;
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug,
        QString("Button edge distance width: %1 height: %2")
            .arg(QString::number(edge_distance_width),
                 QString::number(edge_distance_height)));
    QSize button_size(edge_distance_width,edge_distance_height);
    return button_size;
}

void SettingWindow::CreateRetunButton(const QSize button_size)
{
    SettingWindowButton* return_button=new SettingWindowButton(
        FilePathSystem::GetInstance()
            .GetResourcesPath(resourcesfiletype::ResourcesType::kImages
                              ,"setting_cartonn_exit.png")
        ,button_size*2,"返回到上一个页面",button_size*2,"setting return");
    if(nullptr==return_button)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            QString("Failed to create the %1 button").arg("setting return"));
    }

    return_button->move(this->width()-button_size.width()/2,button_size.height()/2);
    return_button->setParent(this);
    connect(return_button,&QPushButton::clicked,this,&SettingWindow::ReturnToMainWindow);
    this->setting_right_buttons_.push_back(return_button);
}

void SettingWindow::CreateStartButton(const QSize button_size)
{
    SettingWindowButton* start_button=new SettingWindowButton(
        FilePathSystem::GetInstance().GetResourcesPath(
            resourcesfiletype::ResourcesType::kImages,"setting_cartonn_start_up.png"),
        button_size*2,"开始",button_size*2,"setting start"
        ,FilePathSystem::GetInstance().GetResourcesPath(
            resourcesfiletype::ResourcesType::kImages,"setting_cartonn_start_down.png"));
    if(nullptr==start_button)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            QString("Failed to create the %1 button").arg("setting start"));
    }

    start_button->move(this->width()-button_size.width()/2,
                       button_size.height()*6+button_size.height()/2);
    start_button->setParent(this);
    this->setting_right_buttons_.push_back(start_button);
}

SettingWindow::~SettingWindow()
{
    delete this->basic_setting_window_;
    delete this->enviroment_setting_window_;
    delete this->more_setting_window_;
    for(SettingWindowButton* button:setting_left_buttons_)
    {
        delete button;
    }

    for(SettingWindowButton* button:setting_right_buttons_)
    {
        delete button;
    }
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    FileWriteSystem::GetInstance().OutMessage(
        FileWriteSystem::MessageTypeBit::kDebug,
        "The user closes the window using the close event in the upper-right corner");
    FileWriteSystem::GetInstance().EndWirteLine();
}

void SettingWindow::paintEvent(QPaintEvent *event)
{
    QPixmap background_image=QPixmap::fromImage(
        FileReadSystem::GetInstance().ReadImageFile(
            FilePathSystem::GetInstance().GetResourcesPath(
                resourcesfiletype::ResourcesType::kImages,
                "background_picture.png")));

    if(background_image.isNull())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "The background image fails to be read. Check the cause of the failure");
    }

    QBrush brush(background_image);
    QPainter painter(this);
    painter.fillRect(this->rect(),brush);

    QWidget::paintEvent(event);
}

void SettingWindow::HandleButtonClicked()
{
    // Ensure that the same click event is not triggered twice
    if(this->processing_button_click_)
        return;

    // Returns a pointer to the object that sent the signal
    // (in this case SettingWindowButton)
    SettingWindowButton* clicked_button=qobject_cast<SettingWindowButton*>(sender());
    if(nullptr==clicked_button)
        return;

    // Handle click event wait
    this->processing_button_click_=true;

    // Close the current subwindow
    if(this->basic_setting_window_->isVisible())
    {
        this->basic_setting_window_->close();
    }
    else if(this->more_setting_window_->isVisible())
    {
        this->more_setting_window_->close();
    }
    else if(this->enviroment_setting_window_->isVisible())
    {
        this->enviroment_setting_window_->close();
    }

    // show the current subwindow
    if(clicked_button==this->setting_left_buttons_[0])
    {
        this->basic_setting_window_->show();
    }
    else if(clicked_button==this->setting_left_buttons_[1])
    {
        this->more_setting_window_->show();
    }
    else if(clicked_button==this->setting_left_buttons_[2])
    {
        this->enviroment_setting_window_->show();
    }

    // The click event has been processed
    this->processing_button_click_=false;
}

void SettingWindow::ReturnToMainWindow()
{
    MainWindow* main_window=new MainWindow();
    if(main_window)
    {
        QTimer::singleShot(200,this,[=](){
            main_window->setGeometry(this->geometry());
            main_window->show();
            this->close();
        });
    }
}
