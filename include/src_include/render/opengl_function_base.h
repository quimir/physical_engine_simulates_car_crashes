/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2024 QuiMir <2546670299@qq.com>.
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

#ifndef RENDER_OPENGLFUNCTIONBASE_H
#define RENDER_OPENGLFUNCTIONBASE_H

#include "qoffscreensurface.h"
#include <QOpenGLFunctions_4_3_Core>
#include <QPair>
#include <QOpenGLContext>

class OpenGLFunctionBase : public QOpenGLFunctions_4_3_Core
{
public:
    OpenGLFunctionBase();

    bool ContextOpenGL();

    bool ResetOpenGL(QSurfaceFormat format);

    ~OpenGLFunctionBase();

private:
    bool DefaultOpenGL();

    bool IsValidContext();

private:
    QOffscreenSurface* surface_;
    QOpenGLContext* openGL_context_;
};

#endif // RENDER_OPENGLFUNCTIONBASE_H
