#ifndef MODEL_H
#define MODEL_H

#include <QOpenGLFunctions_4_5_Core>
#include <QString>
#include <QMap>
#include <QVector>
#include <QDir>
#include <QImage>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model:protected QOpenGLFunctions_4_5_Core
{
public:
    Model(QString const& path,bool gamma=false);

    GLvoid Draw(Shader& shader);

    GLuint TextureFromFile(const QString& path,const QString& directory,bool gamma);

private:
    GLvoid LoadModel(QString const& path);

    GLvoid ProcessNode(aiNode* node,const aiScene* scene);

    Mesh ProcessMesh(aiMesh* mesh,const aiScene* scene);

    QVector<modelattribute::Texture> LoadMaterialTextures(aiMaterial* mat,aiTextureType type,QString type_name);

public:
    // model data
    QVector<modelattribute::Texture> textures_loaded_;
    QVector<Mesh> meshes_;
    QString directory_;
    bool gamma_correction_;
};

#endif // MODEL_H
