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

#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Core>
#include <QTimer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "src_include/render/shader.h"
#include "src_include/render/vertices.h"
#include "src_include/render/first_person_camera.h"
#include <QSharedPointer>

class StartWindow : public QOpenGLWindow,protected QOpenGLFunctions_4_3_Core
{
public:
    StartWindow(QRect screen_size,QMap<QString,QMap<QString,QList<QString>>> render_map);

    void initializeGL()override;

    void resizeGL(int w,int h)override;

    void paintGL()override;

    void SetSurfaceFormat(QPair<int,int> major_version=QPair<int,int>(4,3), int color_buffer=8, int depth_buffer=24);

    ~StartWindow();

    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *event)override;

private:
    void ReadGLSLMapToShader(QMap<QString,QList<QString>>& glsl_map);

    void ReadRenderingMap(QMap<QString,QMap<QString,QList<QString>>>& render_map);

    void ReadVertices(QMap<QString,QList<QString>>& vertices_map);

    void ReadModel(QMap<QString,QList<QString>>& model_map);

private:
    QRect screen_size_;
    QMap<QString,QMap<QString,QList<QString>>> render_map_;
    QVector<QSharedPointer<Shader>> shaders_;
    QVector<QSharedPointer<Vertices>> vertices_;
    FirstPersonCamera camera_;
    geometricalias::mat4 projection_;


    // QWindow interface
public:
    void mouseMoveEvent(QMouseEvent *event)override;

    // QWindow interface
public:
    void wheelEvent(QWheelEvent *event)override;

protected slots:
    void UpdateViewMatrix(const geometricalias::mat4& view_matrix);
};

#endif // START_WINDOW_H
