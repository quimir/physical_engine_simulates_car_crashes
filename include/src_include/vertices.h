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

#ifndef VERTICES_H
#define VERTICES_H

#include <QVector>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "src_include/geometricalias.h"

class Vertices:protected QOpenGLFunctions_3_3_Core
{
public:
    struct Vertex
    {
        geometricalias::vec3 position;
        geometricalias::vec3 normal;
        geometricalias::vec2 texture_coord;
    };

    Vertices();

    bool LoadObjectFile(const QString& file_path);

    void BindDataToOpenGL();

    qint64 GetIndicesSize()const;

    qint64 GetVerticesSize()const;

    QOpenGLVertexArrayObject& GetVao();

    QOpenGLBuffer GetVbo();

    QOpenGLBuffer GetEbo();

private:
    QVector<Vertex> vertices_;
    QVector<GLuint>indices_;
    QOpenGLVertexArrayObject vao_;
    QOpenGLBuffer vbo_,ebo_;
};

#endif // VERTICES_H
