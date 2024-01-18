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

#ifndef RENDER_MODEL_ANIMATION_ANIMATION_H
#define RENDER_MODEL_ANIMATION_ANIMATION_H

#include <QtAlgorithms>

#include "src_include/render/model_animation/model.h"
#include "src_include/render/model_animation/animdata.h"
#include "src_include/render/model_animation/bone.h"

class Animation
{
public:
    struct AssimpNodeData
    {
        geometricalias::mat4 transformation;
        QString name;
        int children_count;
        QVector<AssimpNodeData> children;
    };

public:
    /**
     * @brief Animation Read the animation from the animation path when the path exists
     * @param animation_path Target animation path
     * @param model Target model
     */
    Animation(const QString& animation_path,Model *model);

    /**
     * @brief FindBone Look for additional bone data that hasn't been added
     * @param name Bone name
     * @return If yes, return skeleton modification, otherwise return nullptr
     */
    Bone *FindBone(const QString& name);

    inline int GetTicksPerSecond()
    {
        return this->ticks_per_second_;
    }

    inline float GetDuration()
    {
        return this->duration_;
    }

    inline const AssimpNodeData &GetRootNode()
    {
        return this->root_node_;
    }

    inline const QMap<QString,BoneInfo>& GetBoneInfoMap()
    {
        return this->bone_info_map_;
    }

private:
    /**
     * @brief ReadMissingBones Read bone data that is not recorded in BoneInfoMap
     * @param animation Need to query whether the bone is in the animation data of BoneInfoMap
     * @param model Model's BoneInfoMap
     */
    void ReadMissingBones(const aiAnimation* animation,Model& model);

    /**
     * @brief ReadHierarchyData Read the node data in the current animation and store it in the animation class node
     * @param dest Animation node data
     * @param src Animation node name
     */
    void ReadHierarchyData(AssimpNodeData& dest,const aiNode* src);

private:
    float duration_;
    /**
     * @brief ticks_per_second_ Animation second counter
     */
    qint32 ticks_per_second_;
    /**
     * @brief bone_ Save bone data
     */
    QVector<Bone> bone_;
    /**
     * @brief root_node_ Save node data
     */
    AssimpNodeData root_node_;
    /**
     * @brief bone_info_map_
     */
    QMap<QString,BoneInfo> bone_info_map_;
};

#endif // RENDER_MODEL_ANIMATION_ANIMATION_H
