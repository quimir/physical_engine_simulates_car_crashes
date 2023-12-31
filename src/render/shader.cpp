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

#include "src_include/render/shader.h"
#include "src_include/file_system/file_write_system.h"

constexpr GLuint kFunctionError=0;
constexpr GLuint kFunctionSuccess=1;

Shader::Shader(bool shader_source_code, const QString &vertex_path, const QString &fragment_path
               , const QString &geometry_path, const QString &tessellation_control_path, const QString &tessellation_evaluation_path, const QString &compute_path)
    :QOpenGLFunctions_4_3_Core()
{
    if(shader_source_code)
    {
        if(!AddShaderSourceCode(vertex_path,fragment_path,geometry_path,tessellation_control_path,tessellation_evaluation_path,compute_path))
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                      ,"The build failed. Please check the log details");
            return;
        }
    }
    else
    {
        if(!AddShaderSourceFile(vertex_path,fragment_path,geometry_path,tessellation_control_path,tessellation_evaluation_path,compute_path))
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                      ,"The build failed. Please check the log details");
            return;
        }
    }
}

Shader::Shader(QOpenGLShader* shader)
{
    if(!this->shader_program_.addShader(shader))
    {
        ErrorMessage(ErrorMessageTypes::Shader);
        return;
    }

    if(!this->shader_program_.create())
    {
        ErrorMessage(ErrorMessageTypes::Create);
        return;
    }

    if(!this->shader_program_.link())
    {
        ErrorMessage(ErrorMessageTypes::Link);
        return;
    }
}

Shader::~Shader()
{
    this->shader_program_.removeAllShaders();
    this->shader_program_.release();
    this->error_map_.clear();
}

GLuint Shader::GetShaderID()
{
    if(!this->shader_program_.isLinked())
    {
        ErrorMessage(ErrorMessageTypes::IsLinked);
        return kFunctionError;
    }
    return this->shader_program_.programId();
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
        return;
    }

    glUniformBlockBinding(this->shader_program_.programId(),block_index,block_binding);
}

QOpenGLShaderProgram &Shader::GetShaderProgram()
{
    return this->shader_program_;
}

QString Shader::GLSLTypesToString(GLSLTypes type)
{
    switch(type)
    {
    case GLSLTypes::Vertex:
        return "vert";
    case GLSLTypes::Fragment:
        return "frag";
    case GLSLTypes::Geometry:
        return "geom";
    case GLSLTypes::TessellationControl:
        return "tesc";
    case GLSLTypes::TessellationEvaluation:
        return "tese";
    case GLSLTypes::Compute:
        return "compute";
    default:
        return QString();
    }
}

GLint Shader::GetUniformLocation(const QString &name)
{
    GLint location=this->shader_program_.uniformLocation(name);

    if(location==-1)
    {
        if(!this->error_map_.contains(name))
        {
            error_map_.insert(name);
            ErrorMessage(ErrorMessageTypes::LocationError,name);
        }
    }

    return location;
}

GLuint Shader::GetUniformBlockIndex(const QString &name)
{
    GLuint index=glGetUniformBlockIndex(shader_program_.programId(),name.toStdString().c_str());

    if(index==GL_INVALID_OPERATION)
    {
        if(!this->error_map_.contains(name))
        {
            this->error_map_.insert(name);
            ErrorMessage(ErrorMessageTypes::BlockIndexError,name);
        }
    }

    return index;
}

GLuint Shader::AddShaderSourceCode(const QString &vertex_path, const QString &fragment_path, const QString &geometry_path, const QString &tessellation_control_path, const QString &tessellation_evaluation_path, const QString &compute_path)
{
    if(!vertex_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceCode(QOpenGLShader::Vertex,vertex_path))
        {
            ErrorMessage(GLSLTypes::Vertex,vertex_path);
            return kFunctionError;
        }
    }
    else
    {
        return kFunctionError;
    }

    if(!fragment_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceCode(QOpenGLShader::Fragment,fragment_path))
        {
            ErrorMessage(GLSLTypes::Fragment,fragment_path);
            return kFunctionError;
        }
    }

    if(!geometry_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceCode(QOpenGLShader::Geometry,geometry_path))
        {
            ErrorMessage(GLSLTypes::Geometry,geometry_path);
        }
    }

    if(!tessellation_control_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceCode(QOpenGLShader::TessellationControl,tessellation_control_path))
        {
            ErrorMessage(GLSLTypes::TessellationControl,tessellation_control_path);
        }
    }

    if(!tessellation_evaluation_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceCode(QOpenGLShader::TessellationEvaluation,tessellation_evaluation_path))
        {
            ErrorMessage(GLSLTypes::TessellationEvaluation,tessellation_evaluation_path);
        }
    }

    if(!compute_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceCode(QOpenGLShader::Compute,compute_path))
        {
            ErrorMessage(GLSLTypes::Compute,compute_path);
        }
    }

    if(!this->shader_program_.create())
    {
        ErrorMessage(ErrorMessageTypes::Create);
        return kFunctionError;
    }

    if(!this->shader_program_.link())
    {
        ErrorMessage(ErrorMessageTypes::Link);
        return kFunctionError;
    }

    return kFunctionSuccess;
}

GLuint Shader::AddShaderSourceFile(const QString &vertex_path, const QString &fragment_path, const QString &geometry_path, const QString &tessellation_control_path, const QString &tessellation_evaluation_path, const QString &compute_path)
{
    if(!vertex_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,vertex_path))
        {
            ErrorMessage(GLSLTypes::Vertex,vertex_path);
            return kFunctionError;
        }
    }
    else
    {
        return kFunctionError;
    }

    if(!fragment_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,fragment_path))
        {
            ErrorMessage(GLSLTypes::Fragment,fragment_path);
            return kFunctionError;
        }
    }

    if(!geometry_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Geometry,geometry_path))
        {
            ErrorMessage(GLSLTypes::Geometry,geometry_path);
        }
    }

    if(!tessellation_control_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceFile(QOpenGLShader::TessellationControl,tessellation_control_path))
        {
            ErrorMessage(GLSLTypes::TessellationControl,tessellation_control_path);
        }
    }

    if(!tessellation_evaluation_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,tessellation_evaluation_path))
        {
            ErrorMessage(GLSLTypes::TessellationEvaluation,tessellation_evaluation_path);
        }
    }

    if(!compute_path.isEmpty())
    {
        if(!this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Compute,compute_path))
        {
            ErrorMessage(GLSLTypes::Compute,compute_path);
        }
    }

    if(!this->shader_program_.create())
    {
        ErrorMessage(ErrorMessageTypes::Create);
        return kFunctionError;
    }

    if(!this->shader_program_.link())
    {
        ErrorMessage(ErrorMessageTypes::Link);
        return kFunctionError;
    }

    return kFunctionSuccess;
}

void Shader::ErrorMessage(ErrorMessageTypes type, const QString &other)
{
    switch(type)
    {
    case ErrorMessageTypes::Create:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Shader create failed");
        break;
    case ErrorMessageTypes::Link:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Shader link failed because: "+this->shader_program_.log());
        break;
    case ErrorMessageTypes::Shader:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add shader failed!");
        break;
    case ErrorMessageTypes::IsLinked:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Shader is not linked please link and then get the ID");
        break;
    case ErrorMessageTypes::LocationError:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,QString("Uniform variable ")+QString(other)
                                                      +QString("not found in the shader."));
        break;
    case ErrorMessageTypes::BlockIndexError:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,QString("Uniform block ")+QString(other)
                                                      +QString("not found in the shader."));
        break;
    }
}

void Shader::ErrorMessage(GLSLTypes type, const QString &path)
{
    switch(type)
    {
    case GLSLTypes::Vertex:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add vertex shader failed path is: "
                                                      +path+this->shader_program_.log());
        break;
    case GLSLTypes::Fragment:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add fragment shader failed path is: "
                                                      +path+this->shader_program_.log());
        break;
    case GLSLTypes::Geometry:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add geometry shader failed path is: "
                                                      +path+this->shader_program_.log());
        break;
    case GLSLTypes::TessellationControl:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add tessllation cotrol shader failed path is: "
                                                      +path+this->shader_program_.log());
        break;
    case GLSLTypes::TessellationEvaluation:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add tessellation evluation shader failed path is: "
                                                      +path+this->shader_program_.log());
        break;
    case GLSLTypes::Compute:
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::Debug
                                                  ,"Add compute shader failed path is: "
                                                      +path+this->shader_program_.log());
        break;
    }
}
