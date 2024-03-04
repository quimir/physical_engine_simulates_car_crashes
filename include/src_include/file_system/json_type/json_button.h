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

#ifndef FILE_SYSTEM_JSON_BUTTON_H
#define FILE_SYSTEM_JSON_BUTTON_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QVariantMap>

namespace jsontype
{
struct JsonButtonKey
{
    QString name;
    QMap<QString,QString> setting;
};

class JsonButton
{
public:
    JsonButton(const QString& path);

    QString GetPath()const;

    bool GetCartoon()const;

    void SetCartoon(bool cartoon);

    JsonButtonKey GetJsonButtonKeyValue(QString key)const;

    QMap<QString,JsonButtonKey> GetButtonMap()const;

    QList<QString> GetButtonMapKeys()const;

    void ParsePathFile();

private:
    void ParseJson(const QJsonObject& root_object);

    QList<JsonButtonKey> ParseButtonKey(const QString& key,const QJsonObject& button_key_object);

    QVariant GetValue(const QJsonObject& object,const QString& key);
private:
    QString path_;

    bool cartoon_;
    QMap<QString,QList<JsonButtonKey>> button_map_;
};
}
#endif // FILE_SYSTEM_JSON_BUTTON_H
