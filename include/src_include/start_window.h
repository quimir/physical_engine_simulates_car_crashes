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
#include <QScopedPointer>

#include "src_include/render/opengl_function_base.h"
#include "src_include/render/shader.h"
#include "src_include/render/model_animation/model.h"
#include "src_include/render/first_person_camera.h"
#include "src_include/file_system/resources_file_type.h"
#include "src_include/render/render_timer.h"

class StartWindow : public QOpenGLWindow,public OpenGLFunctionBase
{
public:
    StartWindow(QRect screen_size,
                QMap<QString,QMap<QString,QList<QString>>> render_map);

    void initializeGL()override;

    void resizeGL(int w,int h)override;

    void paintGL()override;

    ~StartWindow();

    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *event)override;

    void mouseMoveEvent(QMouseEvent *event)override;

    void wheelEvent(QWheelEvent *event)override;

protected slots:
    void UpdateViewMatrix(const geometricalias::mat4& view_matrix);

private:
    void ReadRenderingMap(
    QMap<QString,QMap<QString,QList<QString>>>& render_map);

    bool ReadAnyMap(resourcesfiletype::ResourcesType map_type,
                    QMap<QString,QList<QString>>& any_map);

private:
    QRect screen_size_;
    RenderTimer timer_;

    QMap<QString,QMap<QString,QList<QString>>> render_map_;
    QVector<QScopedPointer<Shader>> shaders_;
    QVector<QScopedPointer<Model>> models_;

    FirstPersonCamera camera_;
    geometricalias::mat4 projection_;
};

#endif // START_WINDOW_H
