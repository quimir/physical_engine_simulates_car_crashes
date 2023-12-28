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

#include <climits>
#include "src_include/model_animation/animator.h"
#include "src_include/file_system/file_wirte_system.h"
#include "src_include/model_animation/bone.h"

Animator::Animator(Animation *animation)
    :current_time_(0),current_animation_(animation)
    ,final_bone_matrices_(QVector<geometricalias::mat4>(100,geometricalias::mat4())),delta_time_((float)INT_MAX)
{
}

void Animator::UpdateAnimation(float delte_time)
{
    this->delta_time_=delte_time;
    if(this->current_animation_)
    {
        this->current_time_+=this->current_animation_->GetTicksPerSecond()*delte_time;
        this->current_time_=fmod(this->current_time_,this->current_animation_->GetDuration());
        CalculateBoneTransform(&this->current_animation_->GetRootNode(),geometricalias::mat4());
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Failed to read the animation class");
        return;
    }
}

void Animator::PlayAnimation(Animation *play_animation)
{
    this->current_animation_=play_animation;
    this->current_time_=0.0f;
}

void Animator::CalculateBoneTransform(const Animation::AssimpNodeData *node, geometricalias::mat4 parent_transfrom)
{
    // Gets the node name and transformation matrix from the animation node data
    QString node_name=node->name;
    geometricalias::mat4 node_transform=node->transformation;

    // Find bones in the current animation
    Bone* bone=this->current_animation_->FindBone(node_name);

    if(bone)
    {
        // If a bone is found, update its status (posture, etc.)
        bone->Update(this->current_time_);
        node_transform=bone->Getlocaltransfrom();
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Failed to read the Bone class");
        return;
    }

    // Calculate the global transformation matrix, multiplied by the parent transformation matrix
    geometricalias::mat4 global_transformation=parent_transfrom*node_transform;
    // Gets the bone information map from the current animation
    QMap<QString,BoneInfo> bone_info_map=this->current_animation_->GetBoneInfoMap();
    if(bone_info_map.find(node_name)!=bone_info_map.end())
    {
        // If the node is in the bone information map, update the final bone matrix
        int index=bone_info_map[node_name].id;
        geometricalias::mat4 offset=bone_info_map[node_name].offset;
        this->final_bone_matrices_[index]=global_transformation*offset;
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("%1 it's been stored on the bone map").arg(node_name));
        return;
    }

    for(int i=0;i<node->children_count;i++)
    {
        CalculateBoneTransform(&node->children[i],global_transformation);
    }
}
