#ifndef BONE_H
#define BONE_H

#include <stdint.h>
#include <limits.h>

#include <QVector>
#include <QList>
#include <QString>
#include <assimp/scene.h>

#include "src_include/geometricalias.h"

class Bone
{
public:
    struct KeyPosition
    {
        geometricalias::vec3 position;
        float time_stamp;
    };

    struct KeyRotation
    {
        geometricalias::quat orientation;
        float time_stamp;
    };

    struct KeyScale
    {
        geometricalias::vec3 scale;
        float time_stamp;
    };

    /**
     * @brief Bone reads keyframes from aiNodeAnim
     * @param name
     * @param id
     * @param channel
     */
    Bone(const QString& name,int id,const aiNodeAnim* channel);

    /**
     * @brief Update interpolates  b/w positions,rotations & scaling keys based on the curren time of
    the animation and prepares the local transformation matrix by combining all keys
    tranformations
     * @param animation_time The duration of the animation
     */
    void Update(float animation_time);

    inline geometricalias::mat4 Getlocaltransfrom()const
    {return this->local_transfrom_;};

    inline QString GetBonename()const
    {return this->name_;};

    inline int GetBoneid()const
    {return this->id_;};

    /**
     * @brief GetPositionIndex Gets the current index on mKeyPositions to interpolate to based on
    the current animation time
     * @param animation_time The duration of the animation
     * @return UINT_MAX or index
     */
    uint32_t GetPositionIndex(float animation_time);

    /**
     * @brief GetRotationIndex Gets the current index on mKeyRotations to interpolate to based on the
    current animation time
     * @param animationTime The duration of the animation
     * @return UINT_MAX or index
     */
    uint32_t GetRotationIndex(float animation_time);

    /**
     * @brief GetScaleIndex Gets the current index on mKeyScalings to interpolate to based on the
    current animation time
     * @param animation_time The duration of the animation
     * @return UINT_MAX or index
     */
    uint32_t GetScaleIndex(float animation_time);

private:
    /**
     * @brief GetScaleFactor Gets normalized value for Lerp & Slerp
     * @param last_time_stamp The timestamp of the last frame
     * @param next_time_stamp The timestamp of the next frame
     * @param animation_time The duration of the animation
     * @return Scale factor about time
     */
    float GetScaleFactor(float last_time_stamp,float next_time_stamp,float animation_time);

    /**
     * @brief InterpolatePosition Gets a linear interpolation of position
     * @param animation_time The duration of the animation
     * @return linear interpolation of position
     */
    geometricalias::mat4 InterpolatePosition(float animationTime);

    /**
     * @brief InterpolateRotation Gets a linear interpolation of rotation
     * @param animation_time The duration of the animation
     * @return linear interpolation of rotation
     */
    geometricalias::mat4 InterpolateRotation(float animation_time);

    /**
     * @brief InterpolateScaling Gets a linear interpolation of scale
     * @param animation_time The duration of the animation
     * @return linear interpolation of scale
     */
    geometricalias::mat4 InterpolateScaling(float animation_time);

private:
    /* Bone data */

    // Save bone position
    QVector<KeyPosition> positions_;
    // Save bone rotation
    QVector<KeyRotation> rotations_;
    // Save bone scale
    QVector<KeyScale> scales_;
    // Save bone position number
    uint32_t num_positions_;
    // Save bone rotation number
    uint32_t num_rotations_;
    // Save bone scale number
    uint32_t num_scalings_;

    // Animation local transformation matrix
    geometricalias::mat4 local_transfrom_;
    // Bone name
    QString name_;
    // Bone id
    int id_;
};


#endif // BONE_H
