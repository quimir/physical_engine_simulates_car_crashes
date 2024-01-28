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

#include <QFile>
#include <QString>
#include <QVector>
#include <QOpenGLTexture>
#include <QScopedPointer>
#include <QMap>

#include "src_include/render/opengl_function_base.h"

/**
 * @brief The RenderTexture class This class is used to load the texture map
 * to be rendered. It is only available via GetInstance(), which ensures that
 * it is only initialized once. The memory is controlled by the RAII.
 */
class RenderTexture:public OpenGLFunctionBase
{
public:
    enum class TextureType
    {
        kTextureDiffuse=0,
        kTextureSpecular,
        kTextureNormal,
        kTextureHeight
    };

public:
    static RenderTexture& GetInstance();

    GLuint LoadTexture(const QString& path,float gamma=1.0f);

    GLuint LoadCubeMap(QVector<QString> faces,float gamma=1.0f);

    QString TextureTypeToString(TextureType type)const;

    QOpenGLTexture* GetTexture();

    ~RenderTexture();

private:
    static RenderTexture& Instance();

    RenderTexture();

    QImage ApplyGammaCorrection(const QImage& input_image,float gamma);

    GLenum GetOpenGLFormat(const QImage& image);

private:
    QOpenGLTexture* texture_;

    QMap<TextureType,QString> texture_type_map_;
};

#endif // RENDER_RENDER_TEXTURE_H
