#ifndef FILE_SYSTEM_JSONTYPE_H
#define FILE_SYSTEM_JSONTYPE_H

#include "json_data/json_data.h"
#include "json_basic_setting.h"
#include "json_button.h"
#include "json_more_setting.h"
#include "json_environment_setting.h"
#include <QObject>

namespace jsonType
{
class JsonType:public QObject
{
    Q_OBJECT
public:
    static JsonType& GetInstance(const QString& json_file_index_path);

private:
    void ParseJsonObject(const QJsonObject& json_object);

    static JsonType& Instance(const QString& json_file_index_path);

    JsonType(const QString& json_file_index_path);

signals:
    void ResourceLoadingError();

private:
    QString path_;

    JsonData* json_data_;
    JsonBasicSetting* json_basic_setting_;
    JsonButton* json_button_;
    JsonMoreSetting* json_more_setting_;
    JsonEnvironmentSetting* json_environment_setting_;
};
}

#endif // FILE_SYSTEM_JSONTYPE_H
