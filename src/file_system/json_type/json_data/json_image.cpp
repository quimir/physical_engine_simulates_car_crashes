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



#include "src_include/file_system/json_type/json_data/json_image.h"
#include "src_include/file_system/file_write_system.h"

namespace jsonType
{

JsonImage::JsonImage(const QJsonObject &json_object)
{
    InitJsonImage(json_object);
}

bool JsonImage::GetVideoOrImage() const
{
    return this->video_or_image_;
}

void JsonImage::SetVideoOrImage(bool new_video_or_image)
{
    this->video_or_image_=new_video_or_image;
}

QVector<BackGround> JsonImage::GetBackGround() const
{
    return this->back_ground_;
}

void JsonImage::SetBackGround(QVector<BackGround> new_back_ground)
{
    if(new_back_ground.isEmpty())
    {
        return;
    }

    this->back_ground_=new_back_ground;
}

void JsonImage::SetBackGround(quint32 index, BackGround new_back_ground)
{
    this->back_ground_[index]=new_back_ground;
}

void JsonImage::InitJsonImage(const QJsonObject &json_object)
{
    if(json_object.isEmpty())
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "Json iamge object load failed!");
        return;
    }

    this->json_object_=json_object;
    ParseImage(this->json_object_);
}

void JsonImage::ResetJsonImage(const QJsonObject &json_object)
{
    InitJsonImage(json_object);
}

void JsonImage::ParseImage(const QJsonObject &image_object)
{
    QVariantMap image_map=image_object.toVariantMap();

    if(image_map.contains("video_or_image"))
    {
        this->video_or_image_=image_map["video_or_image"].toBool();
    }

    if(!this->video_or_image_)
    {
        QVariantMap background_map=image_map["background"].toMap();

        for(auto it=background_map.constBegin();it!=background_map.constEnd();it++)
        {
            QString name=it.key();
            QString path=it.value().toString();

            BackGround back_ground{name,path};

            this->back_ground_.push_back(back_ground);
        }
    }
}

}
