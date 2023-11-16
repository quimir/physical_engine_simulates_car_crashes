#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <QVector>
#include <QOpenGLFunctions_4_5_Core>

#include "src_include/shader.h"
#include "src_include/modelattribute.h"

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

    void Draw(Shader &shader);

private:
    void SetupMesh();

public:
    QVector<modelattribute::Vertex> vertices_;
    QVector<GLuint> indices_;
    QVector<modelattribute::Texture> textures_;
    GLuint VAO_;
private:
    // render data
    GLuint VBO_,EBO_;
};

#endif // MESH_H
