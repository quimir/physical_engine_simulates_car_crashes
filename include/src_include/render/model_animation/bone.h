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

#ifndef RENDER_MODEL_ANIMATION_BONE_H
#define RENDER_MODEL_ANIMATION_BONE_H

#include <stdint.h>

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
     * @brief Bone Reads keyframes from aiNodeAnim
     * @param name The bone path
     * @param id The bone id
     * @param channel Model node animation data
     */
    Bone(const QString& name,int id,const aiNodeAnim* channel);

    /**
     * @brief Update Interpolates  b/w positions,rotations & scaling keys based on the curren time of
    the animation and prepares the local transformation matrix by combining all keys
    tranformations
     * @param animation_time The duration of the animation
     */
    void Update(float animation_time);

    inline geometricalias::mat4 Getlocaltransfrom()const
    {
        return this->local_transfrom_;
    }

    inline QString GetBonename()const
    {
        return this->name_;
    }

    inline int GetBoneid()const
    {
        return this->id_;
    }

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

    /**
     * @brief positions_ Save bone position
     */
    QVector<KeyPosition> positions_;
    /**
     * @brief rotations_ Save bone rotation
     */
    QVector<KeyRotation> rotations_;
    /**
     * @brief scales_ Save bone scale
     */
    QVector<KeyScale> scales_;
    /**
     * @brief num_positions_ Save bone position number
     */
    uint32_t num_positions_;
    /**
     * @brief num_rotations_ Save bone rotation number
     */
    uint32_t num_rotations_;
    /**
     * @brief num_scalings_ Save bone scale number
     */
    uint32_t num_scalings_;

    /**
     * @brief local_transfrom_ Animation local transformation matrix
     */
    geometricalias::mat4 local_transfrom_;
    /**
     * @brief name_ Bone name
     */
    QString name_;
    /**
     * @brief id_ Bone id
     */
    int id_;
};


#endif // RENDER_MODEL_ANIMATION_BONE_H
