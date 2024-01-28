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

#include <QOpenGLFunctions_4_3_Core>
#include <QPair>
#include <QOpenGLContext>
#include <QScopedPointer>
#include <QOpenGLExtraFunctions>
#include <QOffscreenSurface>

/**
 * @brief The OpenGLFunctionBase class This class is specially used to
 * initialize the OpenGL context. If you want to use and initialize OpenGL,
 * please use this class only. This class guarantees that it will only initialize
 * OpenGL when calling this class for the first time and will not bind the OpenGL
 * context repeatedly unless the function of this class is called specifically.
 * In terms of memory, RAII is used, and there is no need to worry about
 * deallocation. This class of memory will be automatically reclaimed by
 * RAII when Qt's reclaim tree is reclaimed.
 */
class OpenGLFunctionBase : public QOpenGLFunctions_4_3_Core
{
public:
    OpenGLFunctionBase();

    QOpenGLExtraFunctions* GetContextOpenGL();

    bool ResetOpenGL(QSurfaceFormat format);

    ~OpenGLFunctionBase();

private:
    /**
     * @brief DefaultOpenGL Set the default OpenGL Settings as determined by Qt.
     * When this function is called, OpenGL is initialized and context bound,
     * and if ResetOpenGL is not called again, it is the only OpenGL.
     * @return Returns true if OpenGL configuration was successful.
     */
    bool DefaultOpenGL();

    bool IsValidContext();

private:
    QOffscreenSurface* surface_;
    QOpenGLContext* openGL_context_;

    static bool is_initialized_;
};

#endif // RENDER_OPENGLFUNCTIONBASE_H
