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
 * @file       model.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <cstdint>

#include <QOpenGLFunctions_3_3_Core>
#include <QString>
#include <QMap>
#include <QVector>
#include <QDir>
#include <QImage>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "src_include/model_animation/mesh.h"
#include "src_include/model_animation/animdata.h"

class Model:protected QOpenGLFunctions_3_3_Core
{
public:
    Model(QString const& path,bool animation_switch=false,bool gamma=false);

    GLvoid Draw(Shader& shader);

    GLuint TextureFromFile(const QString& path,const QString& directory,bool gamma);

    inline auto& GetBoneInfoMap(){return this->boneinfo_map_;};

    inline uint32_t& GetBoneCout(){return this->bone_counter_;};

private:
    GLvoid LoadModel(QString const& path);

    GLvoid ProcessNode(aiNode* node,const aiScene* scene);

    Mesh ProcessMesh(aiMesh* mesh,const aiScene* scene);

    Mesh ProcessAnimationMesh(aiMesh* mesh,const aiScene* scene);

    QVector<modelattribute::Texture> LoadMaterialTextures(aiMaterial* mat,aiTextureType type,QString type_name);

    void SetVertexBoneDataToDafault(modelattribute::Vertex& vertex);

    void SetVertexBoneData(modelattribute::Vertex& vertex,int bone_id,float weight);

    void ExtractBoneWeightForVertices(QVector<modelattribute::Vertex>& vertices,aiMesh* mesh,const aiScene* scene);

public:
    // model data
    QVector<modelattribute::Texture> textures_loaded_;
    QVector<Mesh> meshes_;
    QString directory_;
    bool gamma_correction_;
    bool animation_switch_;

private:
    QMap<QString,BoneInfo> boneinfo_map_;
    uint32_t bone_counter_;
};

#endif // MODEL_H
