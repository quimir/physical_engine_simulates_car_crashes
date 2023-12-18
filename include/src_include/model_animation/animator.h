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

#ifndef MODEL_ANIMATION_ANIMATOR_H
#define MODEL_ANIMATION_ANIMATOR_H

#include <QVector>
#include <QMap>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "src_include/model_animation/animation.h"
#include "src_include/geometricalias.h"

class Animator
{
public:
    /**
     * @brief Animator Initialize and load the animation class
     * @param animation Animation class that needs to be loaded
     */
    Animator(Animation* animation);

    /**
     * @brief UpdateAnimation Remove the animation differences caused by the device
     * @param delte_time Device difference time
     */
    void UpdateAnimation(float delte_time);

    /**
     * @brief PlayAnimation Reset the animation class
     * @param play_animation The animation class that needs to be updated
     */
    void PlayAnimation(Animation* play_animation);

    /**
     * @brief CalculateBoneTransform The skeletal final transformation matrix of the animation node is computed recursively,
     * and the array storing the final matrix is updated. If the node or skeleton is not found, output debugging information and return.
     * @param node Animation node data
     * @param parent_transfrom Matrix data for calculation
     */
    void CalculateBoneTransform(const Animation::AssimpNodeData* node,geometricalias::mat4 parent_transfrom);

    inline QVector<geometricalias::mat4> GetFinalBoneMatrices()
    {
        return this->final_bone_matrices_;
    }

private:
    QVector<geometricalias::mat4> final_bone_matrices_;

    /**
     * @brief current_animation_ Save the imported animation class
     */
    Animation* current_animation_;
    float current_time_;
    float delta_time_;
};

#endif // MODEL_ANIMATION_ANIMATOR_H
