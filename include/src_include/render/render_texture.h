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

#ifndef RENDER_RENDER_TEXTURE_H
#define RENDER_RENDER_TEXTURE_H

#include <QOpenGLFunctions_4_3_Core>
#include <QFile>
#include <QString>
#include <QVector>

class RenderTexture:private QOpenGLFunctions_4_3_Core
{
public:
    static RenderTexture& GetInstance();

    GLuint TextureFromFile(const QString& path,float gamma=1.0f);

    GLuint LoadCubeMap(QVector<QString> faces,float gamma=1.0f);

private:
    static RenderTexture& instance();

    inline RenderTexture():QOpenGLFunctions_4_3_Core()
    {
    }

    QImage ApplyGammaCorrection(const QImage& input_image,float gamma);

    GLenum GetOpenGLFormat(const QImage& image);
};

#endif // RENDER_RENDER_TEXTURE_H
