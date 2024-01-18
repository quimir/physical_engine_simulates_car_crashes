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

#include "src_include/render/vertices.h"
#include "src_include/file_system/file_write_system.h"
#include <QFile>
#include <QTextStream>
#include "src_include/geometricalias.h"

Vertices::Vertices():QOpenGLFunctions_4_3_Core()
{
    //initializeOpenGLFunctions();

    this->vao_.create();
    this->vao_.bind();

    this->vbo_.create();
    this->vbo_.bind();
    this->vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

    this->ebo_.create();
    this->ebo_.bind();
    this->ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

    this->vao_.release();
}

bool Vertices::Text(QSharedPointer<Shader> shader)
{
    QVector<geometricalias::vec3> vertices;
    QVector<geometricalias::vec4> colors;

    vertices << QVector3D(-1.0f, -1.0f, 0.0f)
             << QVector3D(1.0f, -1.0f, 0.0f)
             << QVector3D(0.0f, 1.0f, 0.0f);

    colors << QVector4D(1.0f, 0.0f, 0.0f, 1.0f)
           << QVector4D(0.0f, 1.0f, 0.0f, 1.0f)
           << QVector4D(0.0f, 0.0f, 1.0f, 1.0f);

    this->vao_.bind();
    this->vbo_.bind();

    this->vbo_.allocate(vertices.constData(),vertices.size()*sizeof(geometricalias::vec3));
    shader->GetShaderProgram().enableAttributeArray(0);
    shader->GetShaderProgram().setAttributeBuffer(0,GL_FLOAT,0,3);

    this->ebo_.bind();
    this->ebo_.allocate(colors.constData(),colors.size()*sizeof(geometricalias::vec4));
    shader->GetShaderProgram().enableAttributeArray(1);
    shader->GetShaderProgram().setAttributeBuffer(1,GL_FLOAT,0,4);

    this->vao_.release();

    return true;
}

bool Vertices::LoadObjectFile(const QString &file_path)
{
    this->vertices_.clear();
    this->indices_.clear();

    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,"Failed to open file: "+file_path);
        return false;
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line=in.readLine().trimmed();
        QStringList partes=line.split(' ',Qt::SkipEmptyParts);

        if(partes.isEmpty())
        {
            continue;
        }

        if(partes[0]=="v")
        {
            // Vertex position
            float x=partes[1].toFloat();
            float y=partes[2].toFloat();
            float z=partes[3].toFloat();
            this->vertices_.push_back({geometricalias::vec3(x,y,z)});
        }
        else if(partes[0]=="vn")
        {
            // Vertex normal
            float nx=partes[1].toFloat();
            float ny=partes[2].toFloat();
            float nz=partes[3].toFloat();
            this->vertices_.last().normal=geometricalias::vec3(nx,ny,nz);
        }
        else if(partes[0]=="vt")
        {
            // Texture coordinates
            float u=partes[1].toFloat();
            float v=partes[2].toFloat();
            this->vertices_.last().texture_coord=geometricalias::vec2(u,v);
        }
        else if(partes[0]=="f")
        {
            // Face(vertex indices)
            QStringList face_parts=partes.mid(1);
            for(const QString& face_part:face_parts)
            {
                QStringList indices=face_part.split('/',Qt::SkipEmptyParts);
                this->indices_.append(indices[0].toUInt()-1);
            }
        }
    }

    file.close();
    return true;
}

void Vertices::BindDataToOpenGL()
{
    this->vao_.bind();

    this->vbo_.bind();
    this->vbo_.allocate(this->vertices_.constData(),static_cast<int>(this->vertices_.size()*sizeof(Vertex)));

    this->ebo_.bind();
    this->ebo_.allocate(this->indices_.constData(),static_cast<int>(this->indices_.size()*sizeof(GLuint)));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),reinterpret_cast<void*>(offsetof(Vertex,position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),reinterpret_cast<void*>(offsetof(Vertex,normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),reinterpret_cast<void*>(offsetof(Vertex,texture_coord)));

    this->vao_.release();
    this->vbo_.release();
    this->ebo_.release();
}

void Vertices::DrawArrays(GLenum mode)
{
    this->vao_.bind();
    glDrawArrays(mode,0,static_cast<GLsizei>(this->vertices_.size()));
    this->vao_.release();
}

void Vertices::DrawElements(GLenum mode)
{
    this->vao_.bind();
    glDrawElements(mode,static_cast<GLsizei>(this->indices_.size()),GL_UNSIGNED_INT,nullptr);
    this->vao_.release();
}

qint64 Vertices::GetIndicesSize() const
{
    return this->indices_.size();
}

qint64 Vertices::GetVerticesSize() const
{
    return this->vertices_.size();
}

QOpenGLVertexArrayObject &Vertices::GetVao()
{
    return this->vao_;
}

QOpenGLBuffer Vertices::GetVbo()
{
    return this->vbo_;
}

QOpenGLBuffer Vertices::GetEbo()
{
    return this->ebo_;
}

Vertices::~Vertices()
{
    this->vao_.destroy();
    this->vbo_.destroy();
    this->ebo_.destroy();
    this->vertices_.clear();
    this->indices_.clear();
}
