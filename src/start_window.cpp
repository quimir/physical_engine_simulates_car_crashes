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

#include "src_include/start_window.h"
#include "qevent.h"
#include "src_include/file_system/file_path_system.h"
#include "src_include/file_system/file_write_system.h"
#include "src_include/file_system/resources_file_type.h"
#include <QMessageBox>

StartWindow::StartWindow(QRect screen_size, QMap<QString,QMap<QString,QList<QString>>> render_map):
    QOpenGLWindow(),OpenGLFunctionBase(),screen_size_(screen_size),timer_(),
    render_map_(render_map),camera_(geometricalias::vec3(0.0f,0.0f,3.0f))
{
    if(this->screen_size_.isEmpty()||render_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "No "+QString(this->screen_size_.isEmpty()?(
                                QString("window screen size"+
                                        QString(this->render_map_.isEmpty()?"and no shader map":""))):"shader map"));
    }

    //SetSurfaceFormat();
    this->setGeometry(this->screen_size_);
    connect(&this->camera_,&FirstPersonCamera::ViewMatrixChanged,this,&StartWindow::UpdateViewMatrix);
}

void StartWindow::initializeGL()
{
    glClearColor(0.05f,0.05f,0.05f,1.0f);
    glEnable(GL_DEPTH_TEST);
    ReadRenderingMap(this->render_map_);
}


void StartWindow::resizeGL(int w, int h)
{
    this->projection_.setToIdentity();
    this->projection_.perspective(this->camera_.GetZoom(),w/float(h),0.01f,100.0f);

    glViewport(0,0,w,h);
}

void StartWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    setCursor(Qt::BlankCursor);

    this->timer_.Start();

    for(int i=0;i<this->shaders_.size();i++)
    {
        this->shaders_[i]->Use();

        this->shaders_[i]->SetMat4("projection",this->projection_);
        this->shaders_[i]->SetMat4("view",this->camera_.GetViewMatrix());
        geometricalias::mat4 model;
        model.translate(geometricalias::vec3(0.0f,0.0f,0.0f));
        model.scale(geometricalias::vec3(1.0f,1.0f,1.0f));
        this->shaders_[i]->SetMat4("model",model);
        this->models_[i]->Draw(this->shaders_[i]);
    }

    this->timer_.Stop();
}

StartWindow::~StartWindow()
{
    unsetCursor();
}

void StartWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        this->camera_.ProcessKeyInput(FirstPersonCamera::cameramovement::kForward,
                                      this->timer_.ElapsedTimeInMilliseconds());
        break;
    case Qt::Key_S:
        this->camera_.ProcessKeyInput(FirstPersonCamera::cameramovement::kBackward,
                                      this->timer_.ElapsedTimeInMilliseconds());
        break;
    case Qt::Key_A:
        this->camera_.ProcessKeyInput(FirstPersonCamera::cameramovement::kLeet,
                                      this->timer_.ElapsedTimeInMilliseconds());
        break;
    case Qt::Key_D:
        this->camera_.ProcessKeyInput(FirstPersonCamera::cameramovement::kRight,
                                      this->timer_.ElapsedTimeInMilliseconds());
        break;
    case Qt::Key_Escape:
        this->close();
        break;
    }

    update();
}

void StartWindow::ReadRenderingMap(
    QMap<QString, QMap<QString, QList<QString> > > &render_map)
{
    QMap<QString,QMap<QString,QList<QString>>>::Iterator it=render_map.begin();

    while(it!=render_map.end())
    {
        QMap<QString,QList<QString>> render_map_value=it.value();
        ReadAnyMap(resourcesfiletype::ResourcesTypeToMapper::GetInstance()
                       .StringToEnum(it.key()),render_map_value);

        it++;
    }
}

bool StartWindow::ReadAnyMap(resourcesfiletype::ResourcesType map_type,
                             QMap<QString, QList<QString> > &any_map)
{
    if(any_map.isEmpty()||map_type==resourcesfiletype::ResourcesType::kNone)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            resourcesfiletype::ResourcesTypeToMapper::GetInstance()
                    .EnumToString(map_type)+"is null!");
        return false;
    }

    QMap<QString,QVector<QString>> shader_paths_map;
    if(map_type==resourcesfiletype::ResourcesType::kGLSL)
    {
        shader_paths_map[Shader::GLSLTypesToString(
                             Shader::GLSLTypes::kVertex).toLower()]
            =QVector<QString>();
        shader_paths_map[Shader::GLSLTypesToString(
                             Shader::GLSLTypes::kFragment).toLower()]
            = QVector<QString>();
        shader_paths_map[Shader::GLSLTypesToString(
                             Shader::GLSLTypes::kGeometry).toLower()]
            = QVector<QString>();
        shader_paths_map[Shader::GLSLTypesToString(
                             Shader::GLSLTypes::kTessellationControl).toLower()]
            = QVector<QString>();
        shader_paths_map[Shader::GLSLTypesToString(
                             Shader::GLSLTypes::kTessellationEvaluation).toLower()]
            = QVector<QString>();
        shader_paths_map[Shader::GLSLTypesToString(
                             Shader::GLSLTypes::kCompute).toLower()]
            = QVector<QString>();
    }

    for(const QString &key:any_map.keys())
    {
        QList<QString> value_codes=any_map.value(key);

        for(QString& map_path:value_codes)
        {
            if(!map_path.isEmpty())
            {
                switch(map_type)
                {
                case resourcesfiletype::ResourcesType::kGLSL:
                {
                    QVector<QString>& shader_paths=shader_paths_map[key.toLower()];
                    shader_paths.push_back(map_path);
                }
                break;
                    break;
                case resourcesfiletype::ResourcesType::kModel:
                {
                    QString file_path=FilePathSystem::GetInstance().GetResourcesPath("model/backpack/"+map_path);
                    Model* model=new Model(file_path);
                    this->models_.push_back(model);
                }
                break;
                default:
                    break;
                }
            }
        }
    }
    
    if(map_type==resourcesfiletype::ResourcesType::kGLSL)
    {
        int shader_count = shader_paths_map[
                               Shader::GLSLTypesToString(
                                   Shader::GLSLTypes::kVertex).toLower()].size();

        for(int i=0;i<shader_count;i++)
        {
            Shader* shader=new Shader(
                true,
                shader_paths_map[Shader::GLSLTypesToString(
                                     Shader::GLSLTypes::kVertex)
                                     .toLower()].value(i),
                shader_paths_map[Shader::GLSLTypesToString(
                                     Shader::GLSLTypes::kFragment)
                                     .toLower()].value(i),
                shader_paths_map[Shader::GLSLTypesToString(
                                     Shader::GLSLTypes::kGeometry)
                                     .toLower()].value(i),
                shader_paths_map[Shader::GLSLTypesToString(
                                     Shader::GLSLTypes::kTessellationControl)
                                     .toLower()].value(i),
                shader_paths_map[Shader::GLSLTypesToString(
                                     Shader::GLSLTypes::kTessellationEvaluation)
                                     .toLower()].value(i),
                shader_paths_map[Shader::GLSLTypesToString(
                                     Shader::GLSLTypes::kCompute)
                                     .toLower()].value(i));
            if(shader->Use())
                this->shaders_.push_back(shader);
        }
    }

    return true;
}

void StartWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(this->camera_.GetFirstMouse())
    {
        this->camera_.SetLastMouseX(event->position().x());
        this->camera_.SetLastMouseY(event->position().y());
        this->camera_.SetFirstMouse();
    }

    float xoffset=event->position().x()-this->camera_.GetLastMouseX();
    float yoffset=this->camera_.GetLastMouseY()-event->position().y();

    this->camera_.SetLastMouseX(event->position().x());
    this->camera_.SetLastMouseY(event->position().y());

    this->camera_.ProcessMouseMovement(xoffset,yoffset);

    update();
}

void StartWindow::wheelEvent(QWheelEvent *event)
{
    float yoffset=event->angleDelta().y();
    this->camera_.ProcessMouseScroll(yoffset);

    update();
}

void StartWindow::UpdateViewMatrix(const geometricalias::mat4 &view_matrix)
{
    QVector<int> index;
    for(int i=0;i<this->shaders_.size();i++)
    {
        if(!this->shaders_[i]->Use())
        {
            FileWriteSystem::GetInstance().OutMessage(
                FileWriteSystem::MessageTypeBit::kDebug,
                "No shader was built, please recheck if this shader exists, then kill this shader!");
            index.push_back(i);
        }
        else
        {
            this->shaders_[i]->SetMat4("projection",this->projection_);
            this->shaders_[i]->SetMat4("view",view_matrix);
        }
    }

    for(int i=0;i<index.size();i++)
    {
        if(index[i]>=0&&index[i]<this->shaders_.size())
        {
            this->shaders_.removeAt(index[i]);
        }
        else
        {
            FileWriteSystem::GetInstance().OutMessage(
                FileWriteSystem::MessageTypeBit::kDebug,
                "No this shader index");
        }
    }
}
