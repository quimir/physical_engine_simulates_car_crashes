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

#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QOpenGLShaderProgram>
#include <QMap>
#include <QOpenGLFunctions_4_3_Core>

#include "src_include/geometricalias.h"

class Shader:protected QOpenGLFunctions_4_3_Core
{
public:
    enum class GLSLTypes
    {
        Vertex,
        Fragment,
        Geometry,
        TessellationControl,
        TessellationEvaluation,
        Compute,
    };
public:
    Shader(bool shader_source_code
           ,const QString& vertex_path
           ,const QString& fragment_path
           ,const QString& geometry_path=QString()
           ,const QString& tessellation_control_path=QString()
           ,const QString& tessellation_evaluation_path=QString()
           ,const QString& compute_path=QString());

    Shader(QOpenGLShader *shader);

    Shader(const Shader&)=delete;

    ~Shader();

    GLuint GetShaderID();

    bool Use();

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

    void Release();

    QOpenGLShaderProgram& GetShaderProgram();

    static QString GLSLTypesToString(GLSLTypes type);

private:
    enum class ErrorMessageTypes
    {
        Create,
        Link,
        Shader,
        IsLinked,
        LocationError,
        BlockIndexError
    };

private:
    GLint GetUniformLocation(const QString& name);

    GLuint GetUniformBlockIndex(const QString& name);

    GLuint AddShaderSourceCode(const QString& vertex_path,const QString& fragment_path,const QString& geometry_path
                               ,const QString&tessellation_control_path,const QString& tessellation_evaluation_path
                               ,const QString& compute_path);

    GLuint AddShaderSourceFile(const QString& vertex_path,const QString& fragment_path,const QString& geometry_path
                               ,const QString&tessellation_control_path,const QString& tessellation_evaluation_path
                               ,const QString& compute_path);

    void ErrorMessage(ErrorMessageTypes type,const QString& other=QString());

    void ErrorMessage(GLSLTypes type,const QString&path);

private:
    QOpenGLShaderProgram shader_program_;
    QSet<QString> error_map_;
};

#endif // RENDER_SHADER_H
