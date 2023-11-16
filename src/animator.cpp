#include <limits.h>
#include "src_include/animator.h"
#include "src_include/filewirtesystem.h"
#include "src_include/bone.h"

Animator::Animator(Animation *animation)
{
    this->current_time_=0;
    this->current_animation_=animation;
    this->final_bone_matrices_.reserve(100);
    this->delta_time_=(float)INT_MAX;

    for(uint32_t i=0;i<100;i++)
    {
        this->final_bone_matrices_.push_back(geometricalias::mat4());
    }
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
    QString node_name=node->name;
    geometricalias::mat4 node_transform=node->transformation;
    Bone* bone=this->current_animation_->FindBone(node_name);

    if(bone)
    {
        bone->Update(this->current_time_);
        node_transform=bone->Getlocaltransfrom();
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"Failed to read the Bone class");
    }

    geometricalias::mat4 global_transformation=parent_transfrom*node_transform;
    QMap<QString,BoneInfo> bone_info_map=this->current_animation_->GetBoneInfoMap();
    if(bone_info_map.find(node_name)!=bone_info_map.end())
    {
        int index=bone_info_map[node_name].id;
        geometricalias::mat4 offset=bone_info_map[node_name].offset;
        this->final_bone_matrices_[index]=global_transformation*offset;
    }
    else
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("%1 it's been stored on the bone map").arg(node_name));
    }

    for(int i=0;i<node->children_count;i++)
    {
        CalculateBoneTransform(&node->children[i],global_transformation);
    }
}

QVector<geometricalias::mat4> Animator::GetFinalBoneMatrices()
{
    return this->final_bone_matrices_;
}
