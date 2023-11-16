#ifndef ANIMATION_H
#define ANIMATION_H

#include <QtAlgorithms>

#include "model.h"
#include "src_include/animdata.h"
#include "src_include/bone.h"

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
