#ifndef ANIMDATA_H
#define ANIMDATA_H

#include "src_include/geometricalias.h"

struct BoneInfo
{
    //id is index in finalBoneMatrices
    int id;

    //offset matrix transforms vertex from model space to bone space
    geometricalias::mat4 offset;
};

#endif // ANIMDATA_H
