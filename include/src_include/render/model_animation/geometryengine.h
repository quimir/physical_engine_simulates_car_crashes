#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QOpenGLTexture>

using namespace std;
namespace geometryengine
{
struct VertexData
{
    QVector3D position;
    QVector3D tangent;
    QVector3D normal;
    QVector2D texcoord;
};

struct MeshBuffer
{
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    int vertexNum;
    int indiceNum;

    MeshBuffer() : indexBuf(QOpenGLBuffer::IndexBuffer)
    {
        arrayBuf.create();
        indexBuf.create();
    }

    ~MeshBuffer()
    {
        arrayBuf.destroy();
        indexBuf.destroy();
    }

    void Init(VertexData* vertex, int num)
    {
        vertexNum = num;
        arrayBuf.bind();
        arrayBuf.allocate(vertex, vertexNum * static_cast<int>(sizeof(VertexData)));
    }

    void Init(GLushort* indice, int num)
    {
        indiceNum = num;
        indexBuf.bind();
        indexBuf.allocate(indice, indiceNum * static_cast<int>(sizeof(GLushort)));
    }

    void bind()
    {
        arrayBuf.bind();
        indexBuf.bind();
    }
};

struct Mesh
{
    string name;
    MeshBuffer* buffer = nullptr;
    QOpenGLTexture* albedo;
};

class Model
{
private:
    vector<Mesh*> vecMesh;
public:
    void Push(Mesh* mesh)
    {
        vecMesh.emplace_back(mesh);
    }
    MeshBuffer* GetMeshBuffer(size_t idx) { return vecMesh[idx]->buffer;}
    Mesh* GetMesh(size_t idx) { return vecMesh[idx];}
    size_t Count() { return vecMesh.size();}
};

class GeometryEngine
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    bool loadObj(string path, Model*& pModel);
    void drawObj(string path,QOpenGLShaderProgram* program,bool bTess = false);
    void drawObj(MeshBuffer* meshBuffer, QOpenGLShaderProgram* program,bool bTess = false);


    void CalTangent(VertexData& vertex0, VertexData& vertex1, VertexData& vertex2);

private:
    void processNode(const string& path, aiNode *node, const aiScene *scene);
    void processMesh(vector<VertexData>& vertices, vector<GLushort>& indices, QOpenGLTexture*& albedo, aiMesh *mesh, const aiScene *scen);

    map<string, Model> mapModel;
};
};

#endif // GEOMETRYENGINE_H
