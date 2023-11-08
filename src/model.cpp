#include "src_include/model.h"
#include "src_include/filewirtesystem.h"
#include <cstdlib>
#include <assimp/types.h>

Model::Model(const QString &path, bool gamma):gamma_correction_(gamma)
{
    LoadModel(path);
}

GLvoid Model::Draw(Shader &shader)
{
    for(GLuint i=0;i<this->meshes_.size();i++)
    {
        this->meshes_[i].Draw(shader);
    }
}

GLuint Model::TextureFromFile(const QString &path, const QString &directory, bool gamma)
{
    QString filename=QDir(directory).filePath(path);
    QImage image(filename);

    if(image.isNull())
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Failed to load image: %1").arg(filename));
        return 0;
    }

    GLuint texture_id;
    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);

    GLenum format;
    if (image.format() == QImage::Format_RGB888)
    {
        format = GL_RGB;
    }
    else if (image.format() == QImage::Format_RGBA8888)
    {
        format = GL_RGBA;
    }
    else if (image.format() == QImage::Format_Grayscale8)
    {
        format = GL_RED;
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("Unsupported image format: %1").arg(filename));
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D,0,format,image.width(),image.height(),0,format,GL_UNSIGNED_BYTE,image.constBits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture_id;
}

GLvoid Model::LoadModel(const QString &path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene=importer.ReadFile(path.toStdString().c_str(),aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("ERROR::ASSIMP::%1").arg(importer.GetErrorString()));
        return;
    }
    // retrieve the directory path of the filepath
    QDir directory(path);
    directory.cdUp();
    this->directory_=directory.path();

    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode,scene);
}

GLvoid Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i=0;i<node->mNumMeshes;i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
        this->meshes_.push_back(ProcessMesh(mesh,scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i=0;i<node->mNumChildren;i++)
    {
        ProcessNode(node->mChildren[i],scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    // date to fill
    QVector<modelattribute::Vertex> vertices;
    QVector<GLuint> indices;
    QVector<modelattribute::Texture> textures;

    // walk through each of the mesh's vertices
    for(uint32_t i=0;i<mesh->mNumVertices;i++)
    {
        modelattribute::Vertex vertex;
        geometricalias::vec3 verctor;// we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to QVector3D class so we transfer the data to this placeholder QVector3D first.
        // position
        verctor.setX(mesh->mVertices[i].x);
        verctor.setY(mesh->mVertices[i].y);
        verctor.setZ(mesh->mVertices[i].z);
        vertex.position=verctor;
        // normals
        if(mesh->HasNormals())
        {
            verctor.setX(mesh->mNormals[i].x);
            verctor.setY(mesh->mNormals[i].y);
            verctor.setZ(mesh->mNormals[i].z);
            vertex.normal=verctor;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0])// does the mesh contain texture coordinates?
        {
            geometricalias::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex.tex_coords=vec;
            // tangent
            verctor.setX(mesh->mTangents[i].x);
            verctor.setY(mesh->mTangents[i].y);
            verctor.setZ(mesh->mTangents[i].z);
            vertex.tangent=verctor;
            // bitangent
            verctor.setX(mesh->mBitangents[i].x);
            verctor.setY(mesh->mBitangents[i].y);
            verctor.setZ(mesh->mBitangents[i].z);
            vertex.bitangent=verctor;
        }
        else
        {
            vertex.tex_coords=geometricalias::vec2(0.0f,0.0f);
        }
        vertices.push_back(vertex);
    }

    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(uint32_t i=0;i<mesh->mNumFaces;i++)
    {
        aiFace face=mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(uint32_t j=0;j<face.mNumIndices;j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process materials
    aiMaterial* material=scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1.diffuse maps
    QVector<modelattribute::Texture> diffuse_maps=LoadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
    textures+=diffuse_maps;
    // 2.specular maps
    QVector<modelattribute::Texture> specular_maps=LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures+=specular_maps;
    // 3.normal maps
    QVector<modelattribute::Texture> normal_maps=LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures+=normal_maps;
    // 4.height maps
    QVector<modelattribute::Texture> height_maps=LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures+=height_maps;

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices,indices,textures);
}

QVector<modelattribute::Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, QString type_name)
{
    QVector<modelattribute::Texture> textures;
    for(uint32_t i=0;i<mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat->GetTexture(type,i,&str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip=false;
        for(uint32_t j=0;j<this->textures_loaded_.size();j++)
        {
            if(QFileInfo(this->textures_loaded_[j].path).filePath()==QString(str.C_Str()))
            {
                textures.push_back(this->textures_loaded_[j]);
                skip=true;// a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {
            // if texture hasn't been loaded already, load it
            modelattribute::Texture texture;
            texture.id=TextureFromFile(str.C_Str(),this->directory_,this->gamma_correction_);
            texture.type=type_name;
            texture.path=str.C_Str();
            textures.push_back(texture);
            this->textures_loaded_.push_back(texture);// store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
        }
    }

    return textures;
}
