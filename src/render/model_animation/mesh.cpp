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
#include "src_include/render/render_texture.h"

GLvoid Mesh::Draw(Shader *shader)
{
    // bind appropriate textures
    GLuint diffuse_nr=1;
    GLuint spcular_nr=1;
    GLuint normal_nr=1;
    GLuint height_nr=1;

    auto gl=GetContextOpenGL();

    for(qsizetype i=0;i<textures_.size();i++)
    {
        gl->glActiveTexture(GL_TEXTURE+i);// active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        QString number;
        QString name=this->textures_[i].type;
        if(name==RenderTexture::GetInstance().TextureTypeToString(
                RenderTexture::TextureType::kTextureDiffuse))
        {
            number=QString::number(diffuse_nr++);
        }
        else if(name==RenderTexture::GetInstance().TextureTypeToString(
                     RenderTexture::TextureType::kTextureSpecular))
        {
            number=QString::number(spcular_nr++); // transfer unsigned int to string
        }
        else if(name==RenderTexture::GetInstance().TextureTypeToString(
                     RenderTexture::TextureType::kTextureNormal))
        {
            number=QString::number(normal_nr++);// transfer unsigned int to string
        }
        else if(name==RenderTexture::GetInstance().TextureTypeToString(
                     RenderTexture::TextureType::kTextureHeight))
        {
            number=QString::number(height_nr++);// transfer unsigned int to string
        }

        // now set the sampler to the correct texture unit
        shader->SetUint(QString(name+number),i);
        // and finally bind the texture
        gl->glBindTexture(GL_TEXTURE_2D,this->textures_[i].id);
    }

    int offset=0;
    SetVertexAttribute(shader,"a_position",offset,3);
    offset+=sizeof(geometricalias::vec3);
    SetVertexAttribute(shader,"a_normal",offset,3);
    offset+=sizeof(geometricalias::vec3);
    SetVertexAttribute(shader,"a_tex_coords",offset,2);
    offset+=sizeof(geometricalias::vec2);
    SetVertexAttribute(shader,"a_tangent",offset,3);
    offset+=sizeof(geometricalias::vec3);
    SetVertexAttribute(shader,"a_bitangent",offset,3);
    offset+=sizeof(geometricalias::vec3);
    SetVertexAttribute(shader,"a_bone_ids",offset,modelattribute::KMaxBoneInfluence);
    offset+=sizeof(qint32)*modelattribute::KMaxBoneInfluence;
    SetVertexAttribute(shader,"a_weights",offset,modelattribute::KMaxBoneInfluence);

    // draw mesh
    this->vao_.bind();
    gl->glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(this->indices_.size()),GL_UNSIGNED_INT,nullptr);
    this->vao_.release();

    // always good practice to set everything back to defaults once configured.
    gl->glActiveTexture(0);
}

GLvoid Mesh::SetupMesh()
{
    // create buffers/arrays
    this->vao_.create();
    this->vao_.bind();

    // load data into vertex buffers
    this->vbo_.create();
    this->vbo_.bind();
    // A great thing about structs is that their memory layout is sequential
    // for all its items. The effect is that we can simply pass a pointer to
    // the struct and it translates perfectly to a QVector3D/2 array which again
    //  translates to 3/2 floats which translates to a byte array.
    this->vbo_.allocate(
        this->vertices_.data(),
        static_cast<int>(this->vertices_.size()*sizeof(modelattribute::Vertex)));

    this->ebo_.create();
    this->ebo_.bind();
    this->ebo_.allocate(
        this->indices_.data(),
        static_cast<int>(this->indices_.size()*sizeof(GLuint)));

    this->vao_.release();
    this->vbo_.release();
    this->ebo_.release();
}

GLvoid Mesh::SetVertexAttribute(Shader *shader, QString name, int offset, int tuple_size)
{
    int other_location=shader->GetShaderProgram().attributeLocation(name);
    shader->GetShaderProgram().enableAttributeArray(other_location);
    shader->GetShaderProgram().setAttributeBuffer(
        other_location,GL_FLOAT,offset,tuple_size,sizeof(modelattribute::Vertex));
}
