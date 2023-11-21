/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       startwindow.cpp
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#include "src_include/startwindow.h"
#include "src_include/filewirtesystem.h"

StartWindow::StartWindow(QRect screen_size, Shader *shader):
    screen_size_(screen_size),shader_(shader),vao_(0),vbo_(0),ebo_(0)
{
    this->setGeometry(this->screen_size_);
    if(!this->shader_)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"The shader is not initialized");
    }
}

void StartWindow::initializeGL()
{
    if(!initializeOpenGLFunctions())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Description OpenGL initialization failed");
        return;
    }
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1,&this->vao_);
    glGenBuffers(1,&this->vbo_);
    glBindVertexArray(this->vao_);
    glBindBuffer(GL_ARRAY_BUFFER,this->vbo_);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void StartWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void StartWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    this->shader_->GetShaderProgram().bind();
    glBindVertexArray(this->vao_);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);
    this->shader_->GetShaderProgram().release();
}
