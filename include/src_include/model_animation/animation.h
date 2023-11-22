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
 * @file       animation.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef ANIMATION_H
#define ANIMATION_H

#include <QtAlgorithms>

#include "src_include/model_animation/model.h"
#include "src_include/model_animation/animdata.h"
#include "src_include/model_animation/bone.h"

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
    Animation(const QString& animation_path,Model *model);

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
    void ReadMissingBones(const aiAnimation* animation,Model& model);
    void ReadHierarchyData(AssimpNodeData& dest,const aiNode* src);

private:
    float duration_;
    int ticks_per_second_;
    QVector<Bone> bone_;
    AssimpNodeData root_node_;
    QMap<QString,BoneInfo> bone_info_map_;
};

#endif // ANIMATION_H