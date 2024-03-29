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

#include "src_include/render/model_animation/model.h"
#include "src_include/render/assimp_qt_coversion.h"
#include "src_include/file_system/file_write_system.h"
#include <assimp/types.h>
#include "src_include/render/render_texture.h"

Model::Model(const QString& path, bool animation_switch, float gamma) :gamma_correction_(gamma), animation_switch_(animation_switch)
{
    LoadModel(path);
}

GLvoid Model::Draw(Shader* shader)
{
    for (GLuint i = 0; i < this->meshes_.size(); i++)
    {
        this->meshes_[i]->Draw(shader);
    }
}

GLuint Model::TextureFromFile(const QString& path, const QString& directory, float gamma)
{
    QString filename = QDir(directory).filePath(path);
    return RenderTexture::GetInstance().LoadTexture(filename,gamma);
}

GLvoid Model::LoadModel(const QString& path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path.toStdString().c_str(),
        aiProcess_Triangulate | aiProcess_GenSmoothNormals
            | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  , QString("ERROR::ASSIMP::%1").arg(importer.GetErrorString()));
        return;
    }
    // retrieve the directory path of the filepath
    QDir directory(path);
    directory.cdUp();
    this->directory_ = directory.path();

    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode, scene);
}

GLvoid Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for (uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes_.push_back(ProcessMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (uint32_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh *Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // date to fill
    QVector<modelattribute::Vertex> vertices;
    QVector<GLuint> indices;
    QVector<modelattribute::Texture> textures;

    // walk through each of the mesh's vertices
    for (uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        modelattribute::Vertex vertex;
        if (this->animation_switch_)
        {
            SetVertexBoneDataToDafault(vertex);
            vertex.position = assimpqtcoversion::GetQtVec3(mesh->mVertices[i]);
            vertex.normal = assimpqtcoversion::GetQtVec3(mesh->mNormals[i]);

            if (mesh->mTextureCoords[0])
            {
                geometricalias::vec2 vec(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
                vertex.tex_coord = vec;
            }
            else
            {
                vertex.tex_coord= geometricalias::vec2(0.0f, 0.0f);
            }
        }
        else
        {
            // we declare a placeholder vector since assimp uses its own vector class
            // that doesn't directly convert to QVector3D class so we transfer the
            // data to this placeholder QVector3D first.
            geometricalias::vec3 verctor(mesh->mVertices[i].x,mesh->mVertices[i].y,
                                         mesh->mVertices[i].z);
            // position
            vertex.position = verctor;
            // normals
            if (mesh->HasNormals())
            {
                verctor.setX(mesh->mNormals[i].x);
                verctor.setY(mesh->mNormals[i].y);
                verctor.setZ(mesh->mNormals[i].z);
                vertex.normal = verctor;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0])// does the mesh contain texture coordinates?
            {
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                geometricalias::vec2 vec(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
                vertex.tex_coord = vec;
                // tangent
                verctor.setX(mesh->mTangents[i].x);
                verctor.setY(mesh->mTangents[i].y);
                verctor.setZ(mesh->mTangents[i].z);
                vertex.tangent = verctor;
                // bitangent
                verctor.setX(mesh->mBitangents[i].x);
                verctor.setY(mesh->mBitangents[i].y);
                verctor.setZ(mesh->mBitangents[i].z);
                vertex.bitangent = verctor;
            }
            else
            {
                vertex.tex_coord = geometricalias::vec2(0.0f, 0.0f);
            }
        }
        vertices.push_back(vertex);
    }

    // now wak through each of the mesh's faces (a face is a mesh its triangle)
    // and retrieve the corresponding vertex indices.
    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (uint32_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1.diffuse maps
    QVector<modelattribute::Texture> diffuse_maps = LoadMaterialTextures(
        material,aiTextureType_DIFFUSE,
        RenderTexture::GetInstance().TextureTypeToString(
            RenderTexture::TextureType::kTextureDiffuse));
    textures += diffuse_maps;
    // 2.specular maps
    QVector<modelattribute::Texture> specular_maps = LoadMaterialTextures(
        material, aiTextureType_SPECULAR,
        RenderTexture::GetInstance().TextureTypeToString(
            RenderTexture::TextureType::kTextureSpecular));
    textures += specular_maps;
    // 3.normal maps
    QVector<modelattribute::Texture> normal_maps = LoadMaterialTextures(
        material, aiTextureType_HEIGHT,
        RenderTexture::GetInstance().TextureTypeToString(
            RenderTexture::TextureType::kTextureNormal));
    textures += normal_maps;
    // 4.height maps
    QVector<modelattribute::Texture> height_maps = LoadMaterialTextures(
        material, aiTextureType_AMBIENT,
        RenderTexture::GetInstance().TextureTypeToString(
            RenderTexture::TextureType::kTextureHeight));
    textures += height_maps;

    if(this->animation_switch_)
    {
        ExtractBoneWeightForVertices(vertices,mesh,scene);
    }

    // return a mesh object created from the extracted mesh data
    return new Mesh(vertices, indices, textures);
}

QVector<modelattribute::Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, QString type_name)
{
    QVector<modelattribute::Texture> textures;
    for (uint32_t i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->aiMaterial::GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (uint32_t j = 0; j < this->textures_loaded_.size(); j++)
        {
            if (QFileInfo(this->textures_loaded_[j].path).filePath() == QString(str.C_Str()))
            {
                textures.push_back(this->textures_loaded_[j]);
                skip = true;// a texture with the same filepath has already been
                            // loaded,continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {
            // if texture hasn't been loaded already, load it
            modelattribute::Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory_, this->gamma_correction_);
            texture.type = type_name;
            texture.path = str.C_Str();
            textures.push_back(texture);
            this->textures_loaded_.push_back(texture);// store it as texture
                                                      // loaded for entire model,
                                                      //to ensure we won't
                                                      //unnecessary load duplicate
                                                      //textures.
        }
    }

    return textures;
}

void Model::SetVertexBoneDataToDafault(modelattribute::Vertex& vertex)
{
    for (uint32_t i = 0; i < modelattribute::KMaxBoneInfluence; i++)
    {
        vertex.bone_ids[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

void Model::SetVertexBoneData(modelattribute::Vertex& vertex, int bone_id, float weight)
{
    for (uint32_t i = 0; i < modelattribute::KMaxBoneInfluence; i++)
    {
        if (vertex.bone_ids[i] < 0)
        {
            vertex.weights[i] = weight;
            vertex.bone_ids[i] = bone_id;
            break;
        }
    }
}

void Model::ExtractBoneWeightForVertices(QVector<modelattribute::Vertex>& vertices,
                                         aiMesh* mesh, const aiScene* scene)
{
    QMap<QString, BoneInfo>& bone_info_map = this->boneinfo_map_;
    uint32_t& bone_cout = this->bone_counter_;

    for (uint32_t bone_index = 0; bone_index < mesh->mNumBones; bone_index++)
    {
        int bone_id = -1;
        QString bone_name = mesh->mBones[bone_index]->mName.C_Str();
        if (bone_info_map.find(bone_name) == bone_info_map.end())
        {
            BoneInfo new_bone_info;
            new_bone_info.id = bone_cout;
            new_bone_info.offset = assimpqtcoversion::ConvertMatrixToQtFormat(
                mesh->mBones[bone_index]->mOffsetMatrix);
            bone_info_map[bone_name] = new_bone_info;
            bone_id = bone_cout;
            bone_cout++;
        }
        else
        {
            bone_id = bone_info_map[bone_name].id;
        }

        if (bone_id == -1)
        {
            FileWriteSystem::GetInstance().OutMessage(
                FileWriteSystem::MessageTypeBit::kDebug,
                "Bone id error now is -1");
            return;
        }

        aiVertexWeight* weights = mesh->mBones[bone_index]->mWeights;
        uint32_t num_weights = mesh->mBones[bone_index]->mNumWeights;

        for (uint32_t weight_index = 0; weight_index < num_weights; weight_index++)
        {
            uint32_t vertex_id = weights[weight_index].mVertexId;
            float weight = weights[weight_index].mWeight;

            if (vertex_id > vertices.size())
            {
                FileWriteSystem::GetInstance().OutMessage(
                    FileWriteSystem::MessageTypeBit::kDebug,
                    "Bone weight id > bone weight size no this weight id");
                return;
            }
            SetVertexBoneData(vertices[vertex_id], bone_id, weight);
        }
    }
}
