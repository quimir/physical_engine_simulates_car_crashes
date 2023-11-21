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
 * @file       startwindow.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QTimer>
#include "src_include/shader.h"

class StartWindow : public QOpenGLWindow,protected QOpenGLFunctions_3_3_Core
{
public:
    StartWindow(QRect screen_size, Shader *shader);

    void initializeGL();

    void resizeGL(int w,int h);

    void paintGL();

private:
    QRect screen_size_;
    Shader* shader_;
    GLuint vao_,vbo_,ebo_;
};

#endif // STARTWINDOW_H
