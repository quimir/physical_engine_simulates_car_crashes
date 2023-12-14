/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       mesh.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef MODEL_ANIMATION_MESH_H
#define MODEL_ANIMATION_MESH_H

#include <QObject>
#include <QVector>
#include <QOpenGLFunctions_4_5_Core>

#include "src_include/shader.h"
#include "src_include/model_animation/modelattribute.h"

/**
 * @brief The Mesh class Grid information used to load the model
 */
class Mesh:protected QOpenGLFunctions_3_3_Core
{
public:
    Mesh(QVector<modelattribute::Vertex> vertices,QVector<GLuint> indices,QVector<modelattribute::Texture> textures)
        :vertices_(std::move(vertices)),indices_(std::move(indices)),textures_(std::move(textures))
    {SetupMesh();}

    Mesh(Mesh&& other)noexcept:vertices_(std::move(other.vertices_)),indices_(std::move(other.indices_)),textures_(std::move(other.textures_))
    {SetupMesh();};

    Mesh(const Mesh&other):vertices_(other.vertices_),indices_(other.indices_),textures_(other.textures_)
    {SetupMesh();};

    inline Mesh& operator=(const Mesh& other)
    {
        if(this!=&other)
        {
            this->vertices_=other.vertices_;
            this->indices_=other.indices_;
            this->textures_=other.textures_;
            SetupMesh();
        }
        return *this;
    }

    /**
     * @brief Load and draw the mesh information in the model and bind it to the Shader.
     * This function is called by other classes without explicitly calling it.
     * @param shader Bound shader
     */
    GLvoid Draw(Shader &shader);

private:
    /**
     * @brief SetupMesh Bind the mesh information in the model to OpenGL
     */
    GLvoid SetupMesh();

public:
    /* Mesh data*/

    QVector<modelattribute::Vertex> vertices_;
    QVector<GLuint> indices_;
    QVector<modelattribute::Texture> textures_;
    GLuint VAO_;
private:
    // render data
    GLuint VBO_,EBO_;
};

#endif // MODEL_ANIMATION_MESH_H
