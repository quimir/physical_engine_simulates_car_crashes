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

#include "mesh.h"
#include "animdata.h"

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
