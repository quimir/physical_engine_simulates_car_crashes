/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2024 QuiMir <2546670299@qq.com>.
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

#include <QSurfaceFormat>
#include <QOffscreenSurface>
#include "src_include/render/opengl_function_base.h"
#include "src_include/file_system/file_write_system.h"

bool initialized=false;

OpenGLFunctionBase::OpenGLFunctionBase():QOpenGLFunctions_4_3_Core()
{
    if(!initialized)
    {
        if(DefaultOpenGL())
        {
            initialized=true;
        }
    }
}

bool OpenGLFunctionBase::ContextOpenGL()
{
    if(IsValidContext())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"OpenGL is enabled, and the context is bound.");
        return true;
    }
    
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"OpenGL is not enabled or the context is not bound.");
    return false;
}

bool OpenGLFunctionBase::ResetOpenGL(QSurfaceFormat format)
{
    if(nullptr==this->surface_||nullptr==this->openGL_context_)
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"Scheduling is forbidden without initializing OpenGL.");
        return false;
    }

    this->surface_->setFormat(format);
    this->surface_->create();

    if(!this->openGL_context_->create())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"Open GL Context initialization failed");
        return false;
    }

    this->openGL_context_->doneCurrent();
    if (this->openGL_context_->currentContext() != this->openGL_context_)
    {
        if (!this->openGL_context_->makeCurrent(this->surface_))
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug, "Failed to make the OpenGL context current.");
            return false;
        }
    }


    if(!initializeOpenGLFunctions())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,"Description OpenGL initialization failed!");
        return false;
    }
    
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug, "OpenGL version: " + QString(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    return true;
}

OpenGLFunctionBase::~OpenGLFunctionBase()
{
    if(this->openGL_context_->isValid())
    {
        this->openGL_context_->doneCurrent();
        delete this->openGL_context_;
    }

    if(this->surface_->isValid())
    {
        delete this->surface_;
    }
}

bool OpenGLFunctionBase::DefaultOpenGL()
{
    QSurfaceFormat format;
    QSurfaceFormat::setDefaultFormat(format);

    this->surface_=new QOffscreenSurface();
    this->surface_->setFormat(format);
    this->surface_->create();

    this->openGL_context_=new QOpenGLContext();
    if(!this->openGL_context_->create())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug,"Open GL Context initialization failed");
        return false;
    }

    this->openGL_context_->doneCurrent();
    if (this->openGL_context_->currentContext() != this->openGL_context_)
    {
        if (!this->openGL_context_->makeCurrent(this->surface_))
        {
            FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug, "Failed to make the OpenGL context current.");
            return false;
        }
    }


    if(!initializeOpenGLFunctions())
    {
        FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug
                                                  ,"Description OpenGL initialization failed!");
        return false;
    }
    
    FileWriteSystem::GetInstance().OutMessage(FileWriteSystem::MessageTypeBit::kDebug, "OpenGL version: " + QString(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    return true;
}

bool OpenGLFunctionBase::IsValidContext()
{
    QOpenGLContext* current_context=QOpenGLContext::currentContext();
    return current_context&&current_context->isValid();
}
