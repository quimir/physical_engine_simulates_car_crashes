#include "src_include/render/model_animation/geometryengine.h"
#include "src_include/render/render_texture.h"
#include <QVector2D>
#include <QVector3D>
#include <QVector>


GeometryEngine::GeometryEngine()
{

}

GeometryEngine::~GeometryEngine()
{

}

bool GeometryEngine::loadObj(string path, Model*& pModel)
{
    if(mapModel.find(path) != mapModel.end())
    {
        return true;
    }

    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << import.GetErrorString() ;
        return false;
    }
    string directory = path.substr(0, path.find_last_of('/'));

    processNode(path, scene->mRootNode, scene);
    pModel = &mapModel[path];
    return true;
}

void GeometryEngine::drawObj(MeshBuffer* meshBuffer, QOpenGLShaderProgram* program,bool bTess)
{
    meshBuffer->bind();

    auto gl = QOpenGLContext::currentContext()->extraFunctions();

    int offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int tangentLocation = program->attributeLocation("a_tangent");
    program->enableAttributeArray(tangentLocation);
    program->setAttributeBuffer(tangentLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    if(bTess)
    {
        gl->glPatchParameteri(GL_PATCH_VERTICES, 3);
        gl->glDrawElements(GL_PATCHES, meshBuffer->indiceNum, GL_UNSIGNED_SHORT, nullptr);
    }
    else
    {
        gl->glDrawElements(GL_TRIANGLES, meshBuffer->indiceNum, GL_UNSIGNED_SHORT, nullptr);
    }
}


void GeometryEngine::drawObj(string path,QOpenGLShaderProgram* program,bool bTess)
{
    Model* pModel;
    if(mapModel.find(path) == mapModel.end())
    {
        if(!loadObj(path, pModel))
        {
            return;
        }
    }

    auto vecMesh = mapModel[path];
    for(size_t i = 0;i < vecMesh.Count();i++)
    {
        auto meshBuffer = vecMesh.GetMeshBuffer(i);
        drawObj(meshBuffer,program, bTess);
    }
}

void GeometryEngine::processMesh(vector<VertexData>& vertices, vector<GLushort>& indices, QOpenGLTexture*& albedo, aiMesh *mesh, const aiScene *scene)
{
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        VertexData vertex;
        if(mesh->mVertices)
        {
            vertex.position = QVector3D(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);
        }
        if(mesh->mTextureCoords[0])
        {
            vertex.texcoord = QVector2D(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
        }
        if(mesh->mNormals)
        {
            vertex.normal = QVector3D(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);
            vertex.normal=vertex.normal.normalized();
        }
        if(mesh->mTangents)
        {
            vertex.tangent = QVector3D(mesh->mTangents[i].x,mesh->mTangents[i].y,mesh->mTangents[i].z);
        }
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(static_cast<GLushort>(face.mIndices[j]));
        }
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    for(unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        RenderTexture::GetInstance().LoadTexture(str.C_Str());
        albedo=RenderTexture::GetInstance().GetTexture();
    }
}



void GeometryEngine::processNode(const string& path, aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        vector<VertexData> vertices;
        vector<GLushort> indices;
        QOpenGLTexture* albedo = nullptr;
        aiMesh *aimesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(vertices, indices, albedo, aimesh, scene);

        MeshBuffer* meshBuffer = new MeshBuffer();
        for(size_t i = 0;i < indices.size() / 3; i++)
        {
            CalTangent(vertices[indices[3 * i]],vertices[indices[3 * i + 1]],vertices[indices[3 * i + 2]]);
        }

        meshBuffer->Init(vertices.data(),static_cast<int>(vertices.size()));
        meshBuffer->Init(indices.data(),static_cast<int>(indices.size()));

        Mesh* mesh = new Mesh();
        mesh->name = node->mName.C_Str();
        mesh->buffer = meshBuffer;
        mesh->albedo = albedo;
        mapModel[path].Push(mesh);
    }

    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(path, node->mChildren[i], scene);
    }
}


void GeometryEngine::CalTangent(VertexData& vertex0, VertexData& vertex1, VertexData& vertex2)
{
    float u0 = vertex0.texcoord.x();
    float v0 = vertex0.texcoord.y();

    float u1 = vertex1.texcoord.x();
    float v1 = vertex1.texcoord.y();

    float u2 = vertex2.texcoord.x();
    float v2 = vertex2.texcoord.y();

    float t1 = u1 - u0;
    float b1 = v1 - v0;

    float t2 = u2 - u0;
    float b2 = v2 - v0;

    QVector3D e0 = vertex1.position - vertex0.position;
    QVector3D e1 = vertex2.position - vertex0.position;

    float k = t1 * b2 - b1 * t2;

    QVector3D tangent;
    tangent = k * QVector3D(b2 * e0.x() - b1 * e1.x(),b2 * e0.y() - b1 * e1.y(),b2 * e0.z() - b1 * e1.z());

    QVector<VertexData*> vertexArr = { &vertex0, &vertex1, &vertex2};
    QVector<int> adjoinPlane;
    adjoinPlane.resize(vertexArr.size());
    for(int i = 0;i < vertexArr.size();i++)
    {
        adjoinPlane[i]++;
        float ratio = 1.0f / adjoinPlane[i];
        vertexArr[i]->tangent = vertexArr[i]->tangent * (1 - ratio) + tangent * ratio;
        vertexArr[i]->tangent.normalize();
    }
}
