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

#ifndef RENDER_MODEL_ANIMATION_MODEL_H
#define RENDER_MODEL_ANIMATION_MODEL_H

#include <cstdint>

#include <QString>
#include <QMap>
#include <QVector>
#include <QDir>
#include <QImage>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "src_include/render/model_animation/mesh.h"
#include "src_include/render/opengl_function_base.h"
#include "src_include/render/model_animation/animdata.h"

class Model:public OpenGLFunctionBase
{
public:
    /**
     * @brief Model Load the model if there is animation then load
     * the animation.
     * @param path Model path.
     * @param animation_switch Is animation enabled? It will automatically
     * find the animation file.
     * @param gamma Gamma number or gamma effect.
     */
    Model(QString const& path,bool animation_switch=false,float gamma=1.0f);

    /**
     * @brief Draw Start painting the model and load the shader for
     * shading effects.
     * @param shader Shader object, which is used to color the model to show the coloring effect.
     */
    GLvoid Draw(Shader *shader);

    /**
     * @brief TextureFromFile Find the texture map and bind it to OpenGL.
     * @param path The name of the texture map.
     * @param directory The path of the texture map.
     * @param gamma Gamma effect, generally not enabled by default.
     * @return The ID of the texture in OpenGL after binding is successful.
     */
    GLuint TextureFromFile(const QString& path,const QString& directory,
                           float gamma);

    inline QMap<QString,BoneInfo>& GetBoneInfoMap()
    {
        return this->boneinfo_map_;
    };

    inline uint32_t& GetBoneCout()
    {
        return this->bone_counter_;
    };

private:
    /**
     * @brief LoadModel Read the texture path passed in, look for whether
     * the texture exists, and read the model data according to the node.
     * @param path Model path.
     */
    GLvoid LoadModel(QString const& path);

    /**
     * @brief ProcessNode The node data of the model will read the mesh
     * data in each node data. Repeat the above process to read the
     * remaining node data recursively.
     * @param node Node data of the model.
     * @param scene Scene data of the model.
     */
    GLvoid ProcessNode(aiNode* node,const aiScene* scene);

    /**
     * @brief ProcessMesh Traverse the grid data, reading the bone weight
     * if the animation effect switch is enabled.
     * @param mesh Model mesh.
     * @param scene Model scene.
     * @return All grid data read from the model will be stored in the model.
     */
    Mesh* ProcessMesh(aiMesh* mesh,const aiScene* scene);

    /**
     * @brief LoadMaterialTextures Get the MaterialTexture from the scene
     * texture and get all its Textures.
     * @param mat The Material of the model mesh.
     * @param type The Texture type of the model mesh.
     * @param type_name Types of Texture, respectively
     * texture_diffuse|texture_specular|texture_normal|texture_height.
     * @return All Textures read from the MaterialTextures of the model mesh.
     */
    QVector<modelattribute::Texture> LoadMaterialTextures(aiMaterial* mat,
                                                          aiTextureType type,
                                                          QString type_name);

    /**
     * @brief SetVertexBoneDataToDafault The default bone has an initial id
     * of -1 and a weight of 0.0f.
     * @param vertex Vertex bone data.
     */
    void SetVertexBoneDataToDafault(modelattribute::Vertex& vertex);

    /**
     * @brief SetVertexBoneData Update the bone data set as default to
     * the current bone data.
     * @param vertex Vertex bone data.
     * @param bone_id Now the id of the bone.
     * @param weight Now the weight of the bone.
     */
    void SetVertexBoneData(modelattribute::Vertex& vertex,int bone_id,
                           float weight);

    /**
     * @brief ExtractBoneWeightForVertices Find the bone data in the current
     *  model mesh and update it to the bones.
     * @param vertices Model mesh vertex data.
     * @param mesh Model mesh data.
     * @param scene Model mesh scene data.
     */
    void ExtractBoneWeightForVertices(
    QVector<modelattribute::Vertex>& vertices,
    aiMesh* mesh,const aiScene* scene);

public:
    // model data
    QVector<modelattribute::Texture> textures_loaded_;
    /**
     * @brief meshes_ Mesh data
     */
    QVector<Mesh*> meshes_;
    QString directory_;
    bool gamma_correction_;
    bool animation_switch_;

private:
    QMap<QString,BoneInfo> boneinfo_map_;
    uint32_t bone_counter_;
};

#endif // RENDER_MODEL_ANIMATION_MODEL_H
