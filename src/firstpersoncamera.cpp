#include "src_include/firstpersoncamera.h"


geometricalias::mat4 FirstPersonCamera::GetViewMatrix() const
{
    geometricalias::mat4 view;
    view.lookAt(this->position_,this->position_+this->front_,this->up_);
    return view;
}

geometricalias::vec3 FirstPersonCamera::GetPosition() const
{
    return this->position_;
}

void FirstPersonCamera::UpdateCameraVectors()
{
    geometricalias::vec3 new_front;
    new_front.setX(cos(qDegreesToRadians(this->yaw_))*cos(qDegreesToRadians(this->pitch_)));
    new_front.setY(sin(qDegreesToRadians(this->pitch_)));
    new_front.setZ(sin(qDegreesToRadians(this->yaw_))*cos(qDegreesToRadians(this->pitch_)));
    this->front_=new_front.normalized();
    this->right_=geometricalias::vec3::crossProduct(this->front_,this->world_up_).normalized();
    this->up_=geometricalias::vec3::crossProduct(this->right_,this->front_).normalized();
}

void FirstPersonCamera::ProcessKeyInput(cameramovement direction, float delta_time)
{
    float velocity=this->mouse_sensitivity_*delta_time;

    if(direction==FORWARD)
    {
        this->position_+=this->front_*velocity;
    }
    else if(direction==BACKWARD)
    {
        this->position_-=this->front_*velocity;
    }
    else if(direction==LEFT)
    {
        this->position_-=this->right_*velocity;
    }
    else if(direction==RIGHT)
    {
        this->position_+=this->right_*velocity;
    }

    emit ViewMatrixChanged(GetViewMatrix());
}

void FirstPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch)
{
    xoffset*=mouse_sensitivity_;
    yoffset*=mouse_sensitivity_;

    this->yaw_+=xoffset;
    this->pitch_+=yoffset;

    if(constrain_pitch)
    {
        if(this->pitch_>89.0f)
            this->pitch_=89.0f;
        if(this->pitch_<-89.0f)
            this->pitch_=-89.0f;
    }

    UpdateCameraVectors();

    emit ViewMatrixChanged(GetViewMatrix());
}

void FirstPersonCamera::ProcessMouseScroll(float yoffset)
{
    this->zoom_-=yoffset;
    if(this->zoom_<1.0f)
        this->zoom_=1.0f;
    if(this->zoom_>45.0f)
        this->zoom_=45.0f;

    emit ViewMatrixChanged(GetViewMatrix());
}