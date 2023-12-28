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
#include "src_include/file_system/file_write_system.h"

StartWindow::StartWindow(QRect screen_size, QMap<QString, QList<QString> > shader_map):
    screen_size_(screen_size),shader_map_(shader_map)
{
    if(this->screen_size_.isEmpty()||shader_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"No "+QString(this->screen_size_.isEmpty()?(QString("window screen size"+QString(this->shader_map_.isEmpty()?"and no shader map":""))):"shader map"));
    }
    this->setGeometry(this->screen_size_);
}

void StartWindow::initializeGL()
{
    if(!initializeOpenGLFunctions())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Description OpenGL initialization failed");
        return;
    }
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    ReadShaderMapToShader(this->shader_map_);

}


void StartWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void StartWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void StartWindow::ReadShaderMapToShader(QMap<QString, QList<QString> > &shader_map)
{
    if(shader_map.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Read shader file is null");
    }

    QVector<QString> vertex_path,fragment_path,geometry_path,tessellation_control_path,tessellation_evaluation_path,compute_path;
    QList<QString> shader_keys=shader_map.keys();

    for(const QString&key:shader_keys)
    {
        QList<QString> value_codes=shader_map.value(key);

        for(QString& shader_path:value_codes)
        {
            if(!shader_path.isEmpty())
            {
                if(key=="vert")
                {
                    vertex_path.push_back(shader_path);
                }
                else if(key=="frag")
                {
                    fragment_path.push_back(shader_path);
                }
                else if(key=="geom")
                {
                    geometry_path.push_back(shader_path);
                }
                else if(key=="tesc")
                {
                    tessellation_control_path.push_back(shader_path);
                }
                else if(key=="tese")
                {
                    tessellation_evaluation_path.push_back(shader_path);
                }
                else
                {
                    compute_path.push_back(shader_path);
                }
            }
        }
    }

    for(qlonglong i=0;i<vertex_path.size();i++)
    {
        QSharedPointer<Shader> shader=QSharedPointer<Shader>::create(true,vertex_path[i]
                                                                       ,fragment_path[i],geometry_path[i],tessellation_control_path[i],tessellation_evaluation_path[i],compute_path[i]);
        this->shaders_.append(shader);
    }
}
