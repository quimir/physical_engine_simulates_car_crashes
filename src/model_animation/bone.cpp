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

#include "src_include/model_animation/bone.h"
#include "src_include/assimp_qt_coversion.h"
#include "src_include/file_wirte_system.h"

Bone::Bone(const QString &name, int id, const aiNodeAnim *channel)
    :local_transfrom_(geometricalias::mat4()),name_(std::move(name)),id_(id)
{
    // Get bone position data
    this->num_positions_=channel->mNumPositionKeys;
    for(uint32_t position_index=0;position_index<this->num_positions_;position_index++)
    {
        aiVector3D ai_position=channel->mPositionKeys[position_index].mValue;
        float time_stamp=channel->mPositionKeys[position_index].mTime;
        KeyPosition position_data;
        position_data.position=assimpqtcoversion::GetQtVec3(ai_position);
        position_data.time_stamp=time_stamp;
        this->positions_.push_back(position_data);
    }

    // Get bone rotation data
    this->num_rotations_=channel->mNumRotationKeys;
    for(uint32_t rotation_index=0;rotation_index<this->num_rotations_;rotation_index++)
    {
        aiQuaternion ai_orientation=channel->mRotationKeys[rotation_index].mValue;
        float time_stamp=channel->mRotationKeys[rotation_index].mTime;
        KeyRotation rotation_data;
        rotation_data.orientation=assimpqtcoversion::GetQtQuat(ai_orientation);
        rotation_data.time_stamp=time_stamp;
        this->rotations_.push_back(rotation_data);
    }

    // Get bone scale data
    this->num_scalings_=channel->mNumScalingKeys;
    for(uint32_t scal_index=0;scal_index<this->num_scalings_;scal_index++)
    {
        aiVector3D ai_scale=channel->mScalingKeys[scal_index].mValue;
        float time_stamp=channel->mScalingKeys[scal_index].mTime;
        KeyScale scale_data;
        scale_data.scale=assimpqtcoversion::GetQtVec3(ai_scale);
        scale_data.time_stamp=time_stamp;
        this->scales_.push_back(scale_data);
    }
}

void Bone::Update(float animation_time)
{
    geometricalias::mat4 translation=InterpolatePosition(animation_time);
    geometricalias::mat4 rotation=InterpolateRotation(animation_time);
    geometricalias::mat4 scale=InterpolateScaling(animation_time);
    this->local_transfrom_=translation*rotation*scale;
}

uint32_t Bone::GetPositionIndex(float animation_time)
{
    for(uint32_t index=0;index<this->num_positions_-1;index++)
    {
        if(animation_time<this->positions_[index+1].time_stamp)
        {
            return index;
        }
    }

    FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("No find %1 bone position index id is: %2").arg(name_,QString::number(id_)));
    return UINT_MAX;
}

uint32_t Bone::GetRotationIndex(float animation_time)
{
    for(uint32_t index=0;index<this->num_rotations_-1;index++)
    {
        if(animation_time<this->positions_[index+1].time_stamp)
        {
            return index;
        }
    }

    FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("No find %1 bone rotation index id is: %2").arg(name_,QString::number(id_)));
    return UINT_MAX;
}

uint32_t Bone::GetScaleIndex(float animation_time)
{
    for(uint32_t index=0;index<this->num_scalings_-1;index++)
    {
        if(animation_time<this->scales_[index+1].time_stamp)
        {
            return index;
        }
    }

    FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("No find %1 bone scale index id is: %2").arg(name_,QString::number(id_)));
    return UINT_MAX;
}

float Bone::GetScaleFactor(float last_time_stamp, float next_time_stamp, float animation_time)
{
    float scale_factor=0.0f;
    float mid_way_length=animation_time-last_time_stamp;
    float frame_diff=next_time_stamp-last_time_stamp;
    scale_factor=mid_way_length/frame_diff;
    return scale_factor;
}

geometricalias::mat4 Bone::InterpolatePosition(float animation_time)
{
    geometricalias::mat4 matrix;
    if(1==this->num_positions_)
    {
        geometricalias::vec3 translation_vector=this->positions_[0].position;
        matrix.translate(translation_vector);
        return matrix;
    }

    // Get last time stamp
    uint32_t p0_index=GetPositionIndex(animation_time);
    // Get next time stamp
    uint32_t p1_index=p0_index+1;
    float scale_factor=GetScaleFactor(this->positions_[p0_index].time_stamp,this->positions_[p1_index].time_stamp,animation_time);
    geometricalias::vec3 final_position=geometricalias::lerp(this->positions_[p0_index].position,this->positions_[p1_index].position,scale_factor);
    matrix.translate(final_position);
    return matrix;
}

geometricalias::mat4 Bone::InterpolateRotation(float animation_time)
{
    geometricalias::mat4 matrix;
    if(1==this->num_rotations_)
    {
        geometricalias::quat rotation=this->rotations_[0].orientation;
        rotation.normalize();
        matrix.rotate(rotation);
        return matrix;
    }

    // Get last time stamp
    uint32_t p0_index=GetRotationIndex(animation_time);
    // Get next time stamp
    uint32_t p1_index=p0_index+1;
    float scale_factor=GetScaleFactor(this->rotations_[p0_index].time_stamp,this->rotations_[p1_index].time_stamp,animation_time);
    geometricalias::quat final_rotation=geometricalias::quat::slerp(this->rotations_[p0_index].orientation,this->rotations_[p1_index].orientation,scale_factor);
    final_rotation.normalize();
    matrix.rotate(final_rotation);
    return matrix;
}

geometricalias::mat4 Bone::InterpolateScaling(float animation_time)
{
    geometricalias::mat4 matrix;
    if(1==this->num_scalings_)
    {
        matrix.scale(this->scales_[0].scale);
        return matrix;
    }

    // Get last time stamp
    uint32_t p0_index=GetScaleIndex(animation_time);
    // Get next time stamp
    uint32_t p1_index=p0_index+1;
    float scale_factor=GetScaleFactor(this->scales_[p0_index].time_stamp,this->scales_[p1_index].time_stamp,animation_time);
    geometricalias::vec3 final_scale=geometricalias::lerp(this->positions_[p0_index].position,this->positions_[p1_index].position,scale_factor);
    matrix.scale(final_scale);
    return matrix;
}
