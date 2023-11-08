#ifndef ASSIMP_QT_COVERSION_H
#define ASSIMP_QT_COVERSION_H

#include "src_include/geometricalias.h"

#include <assimp/quaternion.h>
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>

namespace assimpqtcoversion
{
static geometricalias::mat4 ConvertMatrixToQtFormat(const aiMatrix4x4& from)
{
    QMatrix4x4 q_matrix;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            q_matrix(i,j)=from[j][i];
    return q_matrix;
}

static geometricalias::vec3 GetQtVec3(const aiVector3D& vec)
{
    return geometricalias::vec3(vec.x,vec.y,vec.z);
}

static geometricalias::quat GetQtQuat(const aiQuaternion& pOrientation)
{
    return geometricalias::quat(pOrientation.w,pOrientation.x,pOrientation.y,pOrientation.z);
}
}

#endif // ASSIMP_QT_COVERSION_H
