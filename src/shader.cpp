#include "src_include/shader.h"
#include "src_include/filewirtesystem.h"

Shader::Shader(const QString &vertex_path, const QString &fragment_path, const QString &geometry_path, const QString &tessellation_control_path, const QString &tessellation_evaluation_path, const QString &compute_path)
{
    this->shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,vertex_path);
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

    if(this->shader_program_.link())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Shader program linked successfully.");
    }
    else
    {
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
