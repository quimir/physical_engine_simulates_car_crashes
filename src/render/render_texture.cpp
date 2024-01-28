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

#include "src_include/render/render_texture.h"
#include "src_include/file_system/file_read_system.h"

RenderTexture &RenderTexture::GetInstance()
{
    return Instance();
}

GLuint RenderTexture::LoadTexture(const QString &path, float gamma)
{
    if(this->texture_)
    {
        if(this->texture_->isCreated())
        {
            this->texture_->destroy();
            delete this->texture_;
            this->texture_=nullptr;
        }
    }

    // Convert QImage to OpenGL texture
    QImage image=FileReadSystem::GetInstance().ReadImageFile(path);
    if(image.isNull())
    {
        return 0;
    }

    if(gamma!=1.0f)
    {
        image=ApplyGammaCorrection(image,gamma);
    }

    this->texture_=new QOpenGLTexture(image.mirrored());
    if(this->texture_->create())
    {
        this->texture_->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
        this->texture_->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
        this->texture_->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        this->texture_->setMagnificationFilter(QOpenGLTexture::Linear);

        this->texture_->generateMipMaps();
    }
    else
    {
        delete this->texture_;
        return 0;
    }

    return this->texture_->textureId();
}

GLuint RenderTexture::LoadCubeMap(QVector<QString> faces, float gamma)
{
    if(this->texture_)
    {
        if(this->texture_->isCreated())
        {
            this->texture_->destroy();
            delete this->texture_;
            this->texture_=nullptr;
        }
    }

    this->texture_=new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    if(this->texture_->create())
    {
        for(qsizetype i=0;i<faces.size();i++)
        {
            QImage image=FileReadSystem::GetInstance().ReadImageFile(faces[i]);
            if(image.isNull())
            {
                return 0;
            }

            if(gamma!=1.0f)
            {
                image=ApplyGammaCorrection(image,gamma);
            }

            this->texture_->setData(QOpenGLTexture::CubeMapPositiveX + i,
                                    QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                                    image.constBits());

        }

        this->texture_->setMinificationFilter(QOpenGLTexture::Linear);
        this->texture_->setMagnificationFilter(QOpenGLTexture::Linear);
        this->texture_->setWrapMode(QOpenGLTexture::DirectionS,
                                    QOpenGLTexture::ClampToEdge);
        this->texture_->setWrapMode(QOpenGLTexture::DirectionT,
                                    QOpenGLTexture::ClampToEdge);
        this->texture_->setWrapMode(QOpenGLTexture::DirectionR,
                                    QOpenGLTexture::ClampToEdge);

        this->texture_->generateMipMaps();
    }
    else
    {
        delete this->texture_;
        return 0;
    }

    return this->texture_->textureId();
}

QString RenderTexture::TextureTypeToString(TextureType type) const
{
    return this->texture_type_map_.value(type);
}

QOpenGLTexture *RenderTexture::GetTexture()
{
    return this->texture_;
}

RenderTexture::~RenderTexture()
{
    if(this->texture_)
    {
        if(this->texture_->isCreated())
        {
            this->texture_->destroy();
            delete this->texture_;
        }
    }
}

RenderTexture &RenderTexture::Instance()
{
    static RenderTexture instance;
    return instance;
}

RenderTexture::RenderTexture():OpenGLFunctionBase(),texture_(nullptr)
{
    this->texture_type_map_[TextureType::kTextureDiffuse]="texture_diffuse";
    this->texture_type_map_[TextureType::kTextureSpecular]="texture_specular";
    this->texture_type_map_[TextureType::kTextureNormal]="texture_normal";
    this->texture_type_map_[TextureType::kTextureHeight]="texture_height";
}

QImage RenderTexture::ApplyGammaCorrection(const QImage &input_image, float gamma)
{
    QImage corrected_image=input_image;

    // Convert to 32-bit ARGB format
    corrected_image=corrected_image.convertToFormat(QImage::Format_ARGB32);

    uchar *bits = corrected_image.bits();
    int num_pixels = corrected_image.width() * corrected_image.height();
    for (int i = 0; i < num_pixels;i++)
    {
        bits[i * 4] = qPow(bits[i * 4] / 255.0, gamma) * 255.0;
        bits[i * 4 + 1] = qPow(bits[i * 4 + 1] / 255.0, gamma) * 255.0;
        bits[i * 4 + 2] = qPow(bits[i * 4 + 2] / 255.0, gamma) * 255.0;
    }

    return corrected_image;
}

GLenum RenderTexture::GetOpenGLFormat(const QImage &image)
{
    switch(image.format())
    {
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
        return GL_RGBA;
    case QImage::Format_RGB888:
        return GL_RGB;
    case QImage::Format_RGBA8888:
        return GL_RGBA;
    case QImage::Format_Grayscale8:
        return GL_RED;
    case QImage::Format_RGBX8888:
        return GL_RGBA;
    case QImage::Format_BGR888:
        return GL_BGR;
    default:
        return 0;
    }
}
