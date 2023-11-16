#include "src_include/animation.h"
#include "src_include/assimp_qt_coversion.h"
#include "src_include/filewirtesystem.h"

Animation::Animation(const QString &animation_path, Model *model)
{
    Assimp::Importer importer;
    const aiScene* scene=importer.ReadFile(animation_path.toStdString().c_str(),aiProcess_Triangulate);
    if((scene==nullptr)||(scene->mRootNode==nullptr))
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,QString("File Read failed animation path is: %1").arg(animation_path));
        return;
    }

    aiAnimation* animation=scene->mAnimations[0];
    this->duration_=animation->mDuration;
    this->ticks_per_second_=animation->mTicksPerSecond;
    aiMatrix4x4 global_transformation=scene->mRootNode->mTransformation;
    global_transformation=global_transformation.Inverse();
    ReadHierarchyData(this->root_node_,scene->mRootNode);
    ReadMissingBones(animation,*model);
}

Bone *Animation::FindBone(const QString &name)
{
    QList<Bone>::Iterator iter=std::find_if(this->bone_.begin(),this->bone_.end(),[&](const Bone& bone)
                           {return bone.GetBonename()==name;});
    if(iter==this->bone_.end())
        return nullptr;

    return &(*iter);
}

void Animation::ReadMissingBones(const aiAnimation *animation, Model &model)
{
    uint32_t channles_size=animation->mNumChannels;

    QMap<QString,BoneInfo>& bone_info_map=model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
    uint32_t& bone_count=model.GetBoneCout();//getting the m_BoneCounter from Model class

    //reading channels(bones engaged in an animation and their keyframes)
    for(uint32_t i=0;i<channles_size;i++)
    {
        aiNodeAnim* channel=animation->mChannels[i];
        QString bone_name=channel->mNodeName.data;

        //If the bone info map does not have this bone, add it to it
        if(bone_info_map.find(bone_name)==bone_info_map.end())
        {
            bone_info_map[bone_name].id=bone_count;
            bone_count++;
        }
        this->bone_.push_back(Bone(channel->mNodeName.data,bone_info_map[channel->mNodeName.data].id,channel));
    }

    this->bone_info_map_=bone_info_map;
}

void Animation::ReadHierarchyData(AssimpNodeData &dest, const aiNode *src)
{
    if(src==nullptr)
    {
        FileWirteSystem::OutMessage(FileWirteSystem::Debug,"No model node");
        return;
    }

    dest.name=src->mName.data;
    dest.transformation=assimpqtcoversion::ConvertMatrixToQtFormat(src->mTransformation);
    dest.children_count=src->mNumChildren;

    //Read hierarchical nodes recursively
    for(uint32_t i=0;i<src->mNumChildren;i++)
    {
        AssimpNodeData new_data;
        ReadHierarchyData(new_data,src->mChildren[i]);
        dest.children.push_back(new_data);
    }
}
