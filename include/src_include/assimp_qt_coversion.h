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

#ifndef ASSIMP_QT_COVERSION_H
#define ASSIMP_QT_COVERSION_H

#include "src_include/geometricalias.h"

#include <assimp/quaternion.h>
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>

namespace assimpqtcoversion
{

/**
 * @brief ConvertMatrixToQtFormat Convert aiMatrix4x4 to QMatrix4x4
 * @param from Need to convert aiMatrix4x4
 * @return Covert QMatrix4x4
 */
inline static geometricalias::mat4 ConvertMatrixToQtFormat(const aiMatrix4x4& from)
{
    QMatrix4x4 q_matrix;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            q_matrix(i,j)=from[j][i];
    return q_matrix;
}

/**
 * @brief GetQtVec3 Convert aiVerctor3D to QVerctor3D
 * @param vec Need to convert aiVerctor3D
 * @return Convert QVerctor3D
 */
inline static geometricalias::vec3 GetQtVec3(const aiVector3D& vec)
{
    return geometricalias::vec3(vec.x,vec.y,vec.z);
}

/**
 * @brief GetQtQuat Convert aiQuaternion to QQuaternion
 * @param pOrientation Need to convert aiQuaternion
 * @return Convert QQuaternion
 */
inline static geometricalias::quat GetQtQuat(const aiQuaternion& pOrientation)
{
    return geometricalias::quat(pOrientation.w,pOrientation.x,pOrientation.y,pOrientation.z);
}
}

#endif // ASSIMP_QT_COVERSION_H
