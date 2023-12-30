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

#ifndef RENDER_MODEL_ANIMATION_ANIMDATA_H
#define RENDER_MODEL_ANIMATION_ANIMDATA_H

#include "src_include/geometricalias.h"

struct BoneInfo
{
    /**
     * @brief id Is index in finalBoneMatrices
     */
    int id;

    /**
     * @brief offset Matrix transforms vertex from model space to bone space
     */
    geometricalias::mat4 offset;
};

#endif // RENDER_MODEL_ANIMATION_ANIMDATA_H
