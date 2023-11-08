/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       shader.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/01
 * @history
 *****************************************************************************/

#ifndef SHADER_H
#define SHADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QOpenGLShaderProgram>
#include <QMap>
#include <QOpenGLFunctions_4_5_Core>

#include "src_include/geometricalias.h"

class Shader:protected QOpenGLFunctions_4_5_Core
{
public:
    Shader(const QString& vertex_path,const QString& fragment_path,const QString& geometry_path=QString()
           ,const QString&tessellation_control_path=QString(),const QString& tessellation_evaluation_path=QString()
           ,const QString& compute_path=QString());

    void Use();

    void SetBool(const QString& name,bool value);

    void SetInt(const QString& name,GLint value);

    void SetUint(const QString& name,GLuint value);

    void SetFloat(const QString& name,GLfloat value);

    void SetVec2(const QString& name,const geometricalias::vec2& value);

    void SetVec2(const QString& name,GLfloat x,GLfloat y);

    void SetVec3(const QString& name,const geometricalias::vec3& value);

    void SetVec3(const QString& name,GLfloat x,GLfloat y,GLfloat z);

    void SetVec4(const QString& name,const geometricalias::vec4& value);

    void SetVec4(const QString& name,GLfloat x,GLfloat y,GLfloat z,GLfloat w);

    void SetMat2(const QString& name,const geometricalias::mat2& value);

    void SetMat3(const QString& name,const geometricalias::mat3& value);

    void SetMat4(const QString& name,const geometricalias::mat4& value);

    GLuint GetBlockIndex(const QString& name);

    void SetBlockBinding(const GLuint block_index,const GLuint block_binding);

    QOpenGLShaderProgram& GetShaderProgram();

private:
    GLint GetUniformLocation(const QString& name);

    GLuint GetUniformBlockIndex(const QString& name);

private:
    QOpenGLShaderProgram shader_program_;
    QMap<QString,int> error_map_;
};

#endif // SHADER_H
