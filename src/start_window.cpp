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

StartWindow::StartWindow(QRect screen_size, QMap<QString,QMap<QString,QList<QString>>> render_map):
    QOpenGLFunctions_4_3_Core(),screen_size_(screen_size),render_map_(render_map),camera_(geometricalias::vec3(0.0f,0.0f,3.0f))
{
    if(this->screen_size_.isEmpty()||render_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"No "+QString(this->screen_size_.isEmpty()?(QString("window screen size"+QString(this->render_map_.isEmpty()?"and no shader map":""))):"shader map"));
    }

    SetSurfaceFormat();
    this->setGeometry(this->screen_size_);
    connect(&this->camera_,&FirstPersonCamera::ViewMatrixChanged,this,&StartWindow::UpdateViewMatrix);
}

void StartWindow::initializeGL()
{
    if(!initializeOpenGLFunctions())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Description OpenGL initialization failed");
        return;
    }

    glClearColor(1.0f,1.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    ReadRenderingMap(this->render_map_);
    auto vertices=QSharedPointer<Vertices>::create();
    vertices->Text(this->shaders_[0]);
    this->vertices_.push_back(vertices);
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

    this->shaders_[0]->Use();

    geometricalias::mat4 view_matrix=this->camera_.GetViewMatrix();
    this->shaders_[0]->SetMat4("matrix",projection_*view_matrix);

    this->vertices_[0]->GetVao().bind();
    glDrawArrays(GL_TRIANGLES,0,9);
    this->vertices_[0]->GetVao().release();

    this->shaders_[0]->Release();
}

void StartWindow::SetSurfaceFormat(QPair<int, int> major_version, int color_buffer, int depth_buffer)
{
    setSurfaceType(QSurface::OpenGLSurface);

    QSurfaceFormat format;
    format.setVersion(major_version.first,major_version.second);

    format.setRedBufferSize(color_buffer);
    format.setGreenBufferSize(color_buffer);
    format.setBlueBufferSize(color_buffer);
    format.setAlphaBufferSize(color_buffer);

    format.setDepthBufferSize(depth_buffer);

    setFormat(format);
}

StartWindow::~StartWindow()
{
    unsetCursor();
}

void StartWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        this->camera_.ProcessKeyInput(FirstPersonCamera::FORWARD,0.1f);
    }
    else if(event->key()==Qt::Key_S)
    {
        this->camera_.ProcessKeyInput(FirstPersonCamera::BACKWARD,0.1f);
    }
    else if(event->key()==Qt::Key_A)
    {
        this->camera_.ProcessKeyInput(FirstPersonCamera::LEFT,0.1f);
    }
    else if(event->key()==Qt::Key_D)
    {
        this->camera_.ProcessKeyInput(FirstPersonCamera::RIGHT,0.1f);
    }
    else if(event->key()==Qt::Key_Escape)
    {
        this->close();
    }

    update();
}



void StartWindow::ReadGLSLMapToShader(QMap<QString, QList<QString> > &glsl_map)
{
    if(glsl_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Read shader file is null");
        return;
    }

    QMap<QString,QVector<QString>> shader_paths_map;

    shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Vertex).toLower()]=QVector<QString>();
    shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Fragment).toLower()] = QVector<QString>();
    shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Geometry).toLower()] = QVector<QString>();
    shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::TessellationControl).toLower()] = QVector<QString>();
    shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::TessellationEvaluation).toLower()] = QVector<QString>();
    shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Compute).toLower()] = QVector<QString>();

    QList<QString> shader_keys=glsl_map.keys();

    for(const QString& key :shader_keys)
    {
        QList<QString> value_codes=glsl_map.value(key);

        QVector<QString>& shader_paths=shader_paths_map[key.toLower()];

        for(const QString& shader_path:value_codes)
        {
            if(!shader_path.isEmpty())
            {
                shader_paths.push_back(shader_path);
            }
        }
    }

    int shader_count = shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Vertex).toLower()].size();

    for(int i=0;i<shader_count;i++)
    {
        try {
            QSharedPointer<Shader> shader=QSharedPointer<Shader>::create
                (true,shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Vertex).toLower()].value(i),
                 shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Fragment).toLower()].value(i),
                 shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Geometry).toLower()].value(i),
                 shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::TessellationControl).toLower()].value(i),
                 shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::TessellationEvaluation).toLower()].value(i),
                 shader_paths_map[Shader::GLSLTypesToString(Shader::GLSLTypes::Compute).toLower()].value(i));
            this->shaders_.push_back(shader);
        }
        catch (const std::bad_alloc &e)
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug,"Shader create failed!"+QString::number(i)+e.what());
        }
    }
}

void StartWindow::ReadRenderingMap(QMap<QString, QMap<QString, QList<QString> > > &render_map)
{
    QMap<QString,QMap<QString,QList<QString>>>::Iterator it=render_map.begin();

    while(it!=render_map.end())
    {
        if(!QString::compare(it.key(),resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToString(resourcesfiletype::ResourcesType::GLSL),Qt::CaseInsensitive))
        {
            QMap<QString,QList<QString>> glsl_map=it.value();
            ReadGLSLMapToShader(glsl_map);
        }

        // if(!QString::compare(it.key(),resourcesfiletype::ResourcesTypeToMapper::GetInstance().EnumToString(resourcesfiletype::ResourcesType::Obj),Qt::CaseInsensitive))
        // {
        //     QMap<QString,QList<QString>> vertices_map=it.value();
        //     ReadVertices(vertices_map);
        // }

        it++;
    }
}

void StartWindow::ReadVertices(QMap<QString, QList<QString> > &vertices_map)
{
    if(vertices_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug,"Vertices is null!");
        return;
    }

    auto vertices_keys=vertices_map.keys();

    for(const QString& key:vertices_keys)
    {
        QList<QString> value_codes=vertices_map.value(key);

        for(QString& vertices_path:value_codes)
        {
            if(!vertices_path.isEmpty())
            {
                auto vertices=QSharedPointer<Vertices>::create();
                vertices->LoadObjectFile(FilePathSystem::GetInstance().GetResourcesPath(resourcesfiletype::ResourcesType::Obj,vertices_path));
                this->vertices_.push_back(vertices);
            }
        }
    }
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
    for(int i=0;i<this->shaders_.size();i++)
    {
        this->shaders_[i]->Use();
        this->shaders_[i]->SetMat4("matrix",this->projection_*view_matrix);
        this->shaders_[i]->Release();
    }
}
