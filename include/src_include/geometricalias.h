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

#ifndef GEOMETRICALIAS_H
#define GEOMETRICALIAS_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix2x2>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QMatrix2x3>
#include <QMatrix2x4>
#include <QQuaternion>

namespace geometricalias
{
using vec2 = QVector2D;
using vec3 = QVector3D;
using vec4 = QVector4D;
using mat2 = QMatrix2x2;
using mat3 = QMatrix3x3;
using mat4 = QMatrix4x4;
using mat2x3=QMatrix2x3;
using mat2x4=QMatrix2x4;
using quat=QQuaternion;

/**
 * @brief lerp Linear interpolation between two QVector3D, linear interpolation formula :a=a*(1-t)+b*t, will return the linear interpolation value of a.
 * @param v1 Value to interpolate.
 * @param v2 Value to interpolate.
 * @param t Interpolant.
 * @return a
 */
inline static QVector3D lerp(const QVector3D& v1,const QVector3D& v2,float t)
{
    Q_UNUSED(0);
    return v1*(1-t)+v2*t;
}
}

#endif // GEOMETRICALIAS_H
