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

#include "src_include/render/opengl_function_base.h"
#include "src_include/geometricalias.h"

/**
 * @brief The Shader class It generates a wrapper QOpenGLShaderProgram object.
 * Example:
 *   Shader *shader=Shader();
 *   shader->Use();
 *   shader->SetBool(name,value);
 *   shader->Release();
 *   delete shader;
 */
class Shader:public OpenGLFunctionBase
{
public:
    /**
     * @brief The GLSLTypes enum Specifies the type of GLSL.
     * They correspond to:Vertex shader, fragment shader, geometry shader, tessellation
     * control shader, tessellation evaluation shader, compute shader.
     */
    enum class GLSLTypes
    {
        kVertex,
        kFragment,
        kGeometry,
        kTessellationControl,
        kTessellationEvaluation,
        kCompute,
    };

public:
    /**
     * @brief Shader A wrapper QOpenGLShaderProgram object is generated, and if successful,
     * the object is registered in OpenGL.
     * @param shader_source_code Check whether the entered path is a source code file.
     * If yes, enable the corresponding source code function.This value is indispensable.
     * @param vertex_path Path of vertex shader path, this value is required.
     * @param fragment_path Path to the fragment shader, this value is required.
     * @param geometry_path Path of geometry shader, this value can be missing.
     * @param tessellation_control_path Path of tessellation control shader,this value can be missing.
     * @param tessellation_evaluation_path Path of tessellation evaluation shader,this value can be missing.
     * @param compute_path Path of compute shader,this value can be missing.
     */
    explicit Shader(bool shader_source_code
                    ,const QString& vertex_path
                    ,const QString& fragment_path
                    ,const QString& geometry_path=QString()
                    ,const QString& tessellation_control_path=QString()
                    ,const QString& tessellation_evaluation_path=QString()
                    ,const QString& compute_path=QString());

    Shader(QOpenGLShader *shader);

    ~Shader();

    /**
     * @brief GetShaderID If the object has already been linked, return the OpenGL identifier
     * associated with the shader program.
     * @return Returns the OpenGL identifier associated with this shader program
     */
    GLuint GetShaderID();

    /**
     * @brief Use Makes it the current shader program,this is equivalent to
     * QOpenGLShaderProgram's bind() function.
     * @return True if the program was successfully bound; false otherwise.
     */
    bool Use();

    /**
     * @brief SetBool Sets the uniform variable at location in the current context to value.
     * @param name Specifies the location of the uniform variable to be modified.
     * @param value For the scalar commands, specifies the new values to be used for the
     * specified uniform variable.
     */
    void SetBool(const QString& location,bool value);

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

    /**
     * @brief GetBlockIndex Call GetUniformBlockIndex to return the position of unifromblock in the Shader.
     * @param name Specifies the location of the uniform block variable to be modified.
     */
    GLuint GetBlockIndex(const QString& name);

    /**
     * @brief SetBlockBinding Binding points for active uniform blocks are assigned using
     * glUniformBlockBinding.Each of a program's active uniform blocks has a corresponding
     * uniform buffer binding point.If successful, glUniformBlockBinding specifies that
     * program will use the data store of the buffer object bound to the binding point
     * uniformBlockBinding to extract the values of the uniforms in the uniform block
     * identified by uniformBlockIndex.When a program object is linked or re-linked,
     * the uniform buffer object binding point assigned to each of its active uniform
     * blocks is reset to zero.Note that to use this function, you must use GetBlockIndex
     * to get its BlickIndex, so you must call GetBlockIndex before calling this function.
     * @param block_index The index of the active uniform block within program whose
     * binding to assign.
     * @param block_binding Specifies the binding point to which to bind the uniform block
     * with index uniformBlockIndex within program.
     */
    void SetBlockBinding(const GLuint block_index,const GLuint block_binding);

    /**
     * @brief Release The active shader program.Note that this function can only be used
     * if the Use function has been used before and is also linked.A link check is performed
     * and the object is not allowed to be used if it is not registered with OpenGL.
     */
    void Release();

    QOpenGLShaderProgram& GetShaderProgram();

    /**
     * @brief GLSLTypesToString
     * @param type
     * @return
     */
    static QString GLSLTypesToString(GLSLTypes type);

private:
    /**
     * @brief The ErrorMessageTypes enum The type of error that can occur with shaders.
     *  Here's a one-to-one list of possible error cases:
     *  Build errors (input shader path is wrong or OpenGL context is not activated),
     *  link errors (error occurs when OpenGL context or link is not activated, see log
     *  files for details),
     *  Shader errors (error when adding QOpenGLShader* to QOpenGLShaderProgram),
     *  unlinked errors (emitted when not bound to OpenGL),
     *  Uniform Locations errors (emitted when the specified Uniform cannot be found),
     *  Uniform block Locaiton errors (emitted when the specified Uniform block cannot be found).
     */
    enum class ErrorMessageTypes
    {
        kCreateError,
        kLinkError,
        kShaderError,
        kLinkedError,
        kUniformLocationError,
        kUniformBlockIndexError
    };

private:
    /**
     * @brief GetUniformLocation Returns the location of the uniform variable name within this
     * shader program's parameter list. Returns 0 if name is not a valid uniform variable for
     * this shader program.
     * @param uniform_name Name of the uniform variable
     */
    GLint GetUniformLocation(const QString& uniform_name);

    /**
     * @brief GetUniformBlockIndex Returns the location of the uniform block variable name
     * within this shader program's parameter list. Returns 0 if name is not a valid uniform
     * variable for this shader program.
     * @param uniform_block_name Specifies the address an array of characters containing
     * the name of the uniform block whose index to retrieve.
     */
    GLuint GetUniformBlockIndex(const QString& uniform_block_name);

    /**
     * @brief AddShaderSourceCode Add the source file to the shader. If 1 is returned on
     * success, the reason for the failure is written in the log file.
     */
    GLuint AddShaderSourceCode(const QString& vertex_path,const QString& fragment_path,const QString& geometry_path
                               ,const QString& tessellation_control_path,const QString& tessellation_evaluation_path
                               ,const QString& compute_path);

    /**
     * @brief AddShaderSourceFile Add a different shader path, if the path is correct
     * then convert the contents of the path to a source file and add it to the shader
     * and register it with OpenGL.If 1 is returned on success, the reason for the
     * failure is written in the log file.
     */
    GLuint AddShaderSourceFile(const QString& vertex_path,const QString& fragment_path,const QString& geometry_path
                               ,const QString& tessellation_control_path,const QString& tessellation_evaluation_path
                               ,const QString& compute_path);

    /**
     * @brief ErrorMessage Normalize the output error log function
     * @param type Of error message
     * @param other The name of the error that occurred
     */
    void ErrorMessage(ErrorMessageTypes type,const QString& other=QString());

    void ErrorMessage(GLSLTypes type,const QString& path);

private:
    QOpenGLShaderProgram shader_program_;
    QSet<QString> error_map_;
};

#endif // RENDER_SHADER_H
