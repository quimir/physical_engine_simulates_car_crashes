/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       animator.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

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
    Animator(Animation* animation);
    void UpdateAnimation(float delte_time);
    void PlayAnimation(Animation* play_animation);
    void CalculateBoneTransform(const Animation::AssimpNodeData* node,geometricalias::mat4 parent_transfrom);
    QVector<geometricalias::mat4> GetFinalBoneMatrices();
private:
    QVector<geometricalias::mat4> final_bone_matrices_;
    Animation* current_animation_;
    float current_time_;
    float delta_time_;
};

#endif // MODEL_ANIMATION_ANIMATOR_H
