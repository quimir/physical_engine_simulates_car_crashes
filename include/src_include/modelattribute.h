#ifndef MODELATTRIBUTE_H
#define MODELATTRIBUTE_H

#include <cstdlib>

#include <QString>

#include "src_include/geometricalias.h"

namespace modelattribute
{

constexpr unsigned int MAX_BONE_INFLUENCE=4;

struct Vertex
{
    // position
    geometricalias::vec3 position;
    // normal
    geometricalias::vec3 normal;
    // texCoords
    geometricalias::vec2 tex_coords;
    // tangent
    geometricalias::vec3 tangent;
    // bitangent
    geometricalias::vec3 bitangent;
    // bone indexes which will influence this vertex
    int32_t bone_ids[MAX_BONE_INFLUENCE];
    // weights frome each bone
    float_t weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
    uint32_t id;
    QString type;
    QString path;
};

}

#endif // MODELATTRIBUTE_H
