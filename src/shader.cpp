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
 * @file       shader.cpp
 * @version 0.1
 *
 * @author     QuiMir <2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#include "src_include/shader.h"
#include "src_include/filewirtesystem.h"

Shader::Shader(const QString &vertex_path, const QString &fragment_path, const QString &geometry_path, const QString &tessellation_control_path, const QString &tessellation_evaluation_path, const QString &compute_path)
{
    FileWirteSystem::OutMessage(FileWirteSystem::Debug,vertex_path);
    if(this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,vertex_path))
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Shader add From Vertex");
    }

    this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,fragment_path);

    if(!geometry_path.isEmpty())
    {
        this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Geometry,geometry_path);
    }

    if(!tessellation_control_path.isEmpty())
    {
        this->shader_program_.addShaderFromSourceFile(QOpenGLShader::TessellationControl,tessellation_control_path);
    }

    if(!tessellation_evaluation_path.isEmpty())
    {
        this->shader_program_.addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,tessellation_evaluation_path);
    }

    if(!compute_path.isEmpty())
    {
        this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Compute,compute_path);
    }
    this->shader_program_.create();

    if(this->shader_program_.link())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Shader program linked successfully.");
    }
    else
    {
        GLint link_status;
        glGetProgramiv(this->shader_program_.programId(),GL_LINK_STATUS,&link_status);
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Shader program linking failed: %1" ).arg(shader_program_.log()));
    }
}

void Shader::Use()
{
    this->shader_program_.bind();
}

void Shader::SetBool(const QString &name, bool value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetInt(const QString &name, GLint value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetUint(const QString &name, GLuint value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetFloat(const QString &name, GLfloat value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetVec2(const QString &name, const geometricalias::vec2 &value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetVec2(const QString &name, GLfloat x, GLfloat y)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),x,y);
}

void Shader::SetVec3(const QString &name, const geometricalias::vec3 &value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetVec3(const QString &name, GLfloat x, GLfloat y, GLfloat z)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),x,y,z);
}

void Shader::SetVec4(const QString &name, const geometricalias::vec4 &value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetVec4(const QString &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),x,y,z,w);
}

void Shader::SetMat2(const QString &name, const geometricalias::mat2 &value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetMat3(const QString &name, const geometricalias::mat3 &value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

void Shader::SetMat4(const QString &name, const geometricalias::mat4 &value)
{
    this->shader_program_.setUniformValue(GetUniformLocation(name),value);
}

GLuint Shader::GetBlockIndex(const QString &name)
{
    return GetUniformBlockIndex(name);
}

void Shader::SetBlockBinding(const GLuint block_index, const GLuint block_binding)
{
    if(block_index==GL_INVALID_INDEX)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("The bloc index error does not exist occurred in: %1 shader").arg(QString::number(this->shader_program_.programId())));
        return;
    }

    glUniformBlockBinding(this->shader_program_.programId(),block_index,block_binding);
}

QOpenGLShaderProgram &Shader::GetShaderProgram()
{
    return this->shader_program_;
}

GLint Shader::GetUniformLocation(const QString &name)
{
    GLint location=this->shader_program_.uniformLocation(name);

    if(location==-1)
    {
        if(this->error_map_.contains(name))
        {
            error_map_[name]++;
            FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Uniform variable %1 not found in the shader.").arg(name));
        }
    }

    return location;
}

GLuint Shader::GetUniformBlockIndex(const QString &name)
{
    GLuint index=glGetUniformBlockIndex(shader_program_.programId(),name.toStdString().c_str());

    if(index==GL_INVALID_OPERATION)
    {
        if(this->error_map_.contains(name))
        {
            this->error_map_[name]++;
            FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Uniform block %1 not found in the shader.").arg(name));
        }
    }

    return index;
}
