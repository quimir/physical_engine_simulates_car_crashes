/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       geometricalias.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/01
 * @history
 *****************************************************************************/

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
static QVector3D lerp(const QVector3D& v1,const QVector3D& v2,float t)
{
    return v1*(1-t)+v2*t;
}
}

#endif // GEOMETRICALIAS_H
