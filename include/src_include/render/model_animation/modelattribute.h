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

#ifndef RENDER_MODEL_ANIMATION_MODELATTRIBUTE_H
#define RENDER_MODEL_ANIMATION_MODELATTRIBUTE_H

#include <QString>

#include "src_include/geometricalias.h"

namespace modelattribute
{

constexpr quint32 KMaxBoneInfluence=4;

struct Vertex
{
    // position
    geometricalias::vec3 position;
    // normal
    geometricalias::vec3 normal;
    // texCoords
    geometricalias::vec2 tex_coord;
    // tangent
    geometricalias::vec3 tangent;
    // bitangent
    geometricalias::vec3 bitangent;
    // bone indexes which will influence this vertex
    qint32 bone_ids[KMaxBoneInfluence];
    // weights frome each bone
    float weights[KMaxBoneInfluence];
};

struct Texture
{
    quint32 id;
    QString type;
    QString path;
};

}

#endif // RENDER_MODEL_ANIMATION_MODELATTRIBUTE_H
