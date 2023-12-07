/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       firstpersoncamera.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include <QObject>

#include "src_include/geometricalias.h"

namespace camerasetting
{
constexpr float YAW=-90.0f;
constexpr float PITCH=0.0f;
constexpr float SPEED=2.5f;
constexpr float SENSITIVITY=0.1f;
constexpr float ZOOM=45.0f;
}

class FirstPersonCamera : public QObject
{
    Q_OBJECT

public:
    enum cameramovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

public:
    explicit FirstPersonCamera(geometricalias::vec3 position=geometricalias::vec3(0.0f,0.0f,0.0f)
                               ,geometricalias::vec3 up=geometricalias::vec3(0.0f,1.0f,0.0f),
                               float yaw=camerasetting::YAW,float pitch=camerasetting::PITCH,QObject *parent=nullptr)
        :QObject(parent),position_(position),front_(geometricalias::vec3(0.0f,0.0f,-1.0f))
        ,world_up_(up),yaw_(yaw),pitch_(pitch),movement_speed_(camerasetting::SPEED),
        mouse_sensitivity_(camerasetting::SENSITIVITY),zoom_(camerasetting::ZOOM)
    {
        UpdateCameraVectors();
    }

    geometricalias::mat4 GetViewMatrix()const;

    geometricalias::vec3 GetPosition()const;

private:
    void UpdateCameraVectors();

public slots:
    void ProcessKeyInput(FirstPersonCamera::cameramovement direction,float delta_time);

    void ProcessMouseMovement(float xoffset,float yoffset,bool constrain_pitch=true);

    void ProcessMouseScroll(float yoffset);

signals:
    void ViewMatrixChanged(const geometricalias::mat4& view_matrix);

private:
    // camera Attributes
    geometricalias::vec3 position_;
    geometricalias::vec3 front_;
    geometricalias::vec3 up_;
    geometricalias::vec3 right_;
    geometricalias::vec3 world_up_;

    // euler Angles
    float yaw_;
    float pitch_;

    // camera options
    float movement_speed_;
    float mouse_sensitivity_;
    float zoom_;
};

#endif // FIRST_PERSON_CAMERA_H
