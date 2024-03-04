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

#ifndef FILE_SYSTEM_JSON_DATA_JSON_IMAGE_H
#define FILE_SYSTEM_JSON_DATA_JSON_IMAGE_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QVector>

namespace jsontype
{

struct BackGround
{
    QString name;
    QString path;
};

class JsonImage
{
public:
    JsonImage(const QJsonObject& json_object);

    bool GetVideoOrImage()const;

    void SetVideoOrImage(bool new_video_or_image);

    QVector<BackGround> GetBackGround()const;

    void SetBackGround(QVector<BackGround> new_back_ground);

    void SetBackGround(quint32 index,BackGround new_back_ground);

    void ResetJsonImage(const QJsonObject& json_object);

    QJsonObject GetRootObject()const;

private:
    void InitJsonImage(const QJsonObject& json_object);

    void ParseImage(const QJsonObject& image_object);

private:
    QJsonObject root_object_;
    bool video_or_image_;
    QVector<BackGround> back_ground_;
};
}

#endif // FILE_SYSTEM_JSON_DATA_JSON_IMAGE_H
