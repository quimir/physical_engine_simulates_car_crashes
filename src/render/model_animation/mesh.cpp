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

#include "src_include/render/model_animation/mesh.h"

GLvoid Mesh::Draw(Shader &shader)
{
    // bind appropriate textures
    GLuint diffuse_nr=1;
    GLuint spcular_nr=1;
    GLuint normal_nr=1;
    GLuint height_nr=1;

    for(qsizetype i=0;i<textures_.size();i++)
    {
        glActiveTexture(GL_TEXTURE0+i);// active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        QString number;
        QString name=this->textures_[i].type;
        if(name=="texture_diffuse")
        {
            number=QString::number(diffuse_nr++);
        }
        else if(name=="texture_specular")
        {
            number=QString::number(spcular_nr++); // transfer unsigned int to string
        }
        else if(name=="texture_normal")
        {
            number=QString::number(normal_nr++);// transfer unsigned int to string
        }
        else if(name=="texture_height")
        {
            number=QString::number(height_nr++);// transfer unsigned int to string
        }

        // now set the sampler to the correct texture unit
        shader.SetUint(QString(name+number),i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D,this->textures_[i].id);
    }

    // draw mesh
    glBindVertexArray(this->VAO_);
    glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(this->indices_.size()),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

GLvoid Mesh::SetupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1,&this->VAO_);
    glGenBuffers(1,&this->VBO_);
    glGenBuffers(1,&this->EBO_);

    glBindVertexArray(this->VAO_);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER,this->VBO_);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a QVector3D/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER,this->vertices_.size()*sizeof(modelattribute::Vertex),&this->vertices_[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,this->indices_.size()*sizeof(GLuint),&this->indices_[0],GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(modelattribute::Vertex),(void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(modelattribute::Vertex),(void*)offsetof(modelattribute::Vertex,normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(modelattribute::Vertex),(void*)offsetof(modelattribute::Vertex,tex_coords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(modelattribute::Vertex),(void*)offsetof(modelattribute::Vertex,tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(modelattribute::Vertex),(void*)offsetof(modelattribute::Vertex,bitangent));
    // vertex bone ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5,modelattribute::KMaxBoneInfluence,GL_INT,sizeof(modelattribute::Vertex),(void*)offsetof(modelattribute::Vertex,bone_ids));
    // vertex bone weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6,modelattribute::KMaxBoneInfluence,GL_FLOAT,GL_FALSE,sizeof(modelattribute::Vertex),(void*)offsetof(modelattribute::Vertex,weights));
    glBindVertexArray(0);
}
