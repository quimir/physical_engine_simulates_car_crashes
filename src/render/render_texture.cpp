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
#include "src_include/file_system/file_write_system.h"

RenderTexture &RenderTexture::GetInstance()
{
    return instance();
}

GLuint RenderTexture::TextureFromFile(const QString &path, float gamma)
{
    QImage image=FileReadSystem::GetInstance().ReadImageFile(path);
    if(image.isNull())
    {
        return 0;
    }

    if(gamma!=1.0f)
    {
        image=ApplyGammaCorrection(image,gamma);
    }

    GLuint texture_id;
    glGenTextures(1,&texture_id);

    GLenum format=GetOpenGLFormat(image);
    if(!format)
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  , QString("Unsupported image format: ")+path);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width(), image.height(), 0, format, GL_UNSIGNED_BYTE, image.constBits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture_id;
}

GLuint RenderTexture::LoadCubeMap(QVector<QString> faces, float gamma)
{
    GLuint texture_id;
    glGenBuffers(1,&texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP,texture_id);

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

        GLenum format=GetOpenGLFormat(image);
        if(!format)
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                      , QString("Unsupported image format: ")+faces[i]);
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,format,image.width(),image.height(),0,format,GL_UNSIGNED_BYTE,image.constBits());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture_id;
}

RenderTexture &RenderTexture::instance()
{
    static RenderTexture instance;
    return instance;
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
