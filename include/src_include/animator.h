#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QVector>
#include <QMap>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "src_include/animation.h"
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

#endif // ANIMATOR_H
