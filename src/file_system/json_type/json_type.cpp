#include "src_include/file_system/json_type/json_type.h"
#include "src_include/file_system/file_read_system.h"
#include "src_include/file_system/file_path_system.h"

namespace jsonType
{
JsonType &JsonType::GetInstance(const QString &json_file_index_path)
{
    return Instance(json_file_index_path);
}

void JsonType::ParseJsonObject(const QJsonObject &json_object)
{
    for(auto it=json_object.begin();it!=json_object.end();it++)
    {
        QString key=it.key();
        if(key.contains("data",Qt::CaseInsensitive))
        {
            this->json_data_=new JsonData(
                FilePathSystem::GetInstance().GetResourcesPath(
                    resourcesfiletype::ResourcesType::kJson,json_object[key].toString()));
            this->json_data_->PrasePathFile();
        }
        else if(key.contains("basic_setting",Qt::CaseInsensitive))
        {
            this->json_basic_setting_=new JsonBasicSetting();
        }
        else if(key.contains("button",Qt::CaseInsensitive))
        {
            this->json_button_=new JsonButton(
                FilePathSystem::GetInstance().GetResourcesPath(
                    resourcesfiletype::ResourcesType::kJson,json_object[key].toString()));
            this->json_button_->ParsePathFile();
        }
        else if(key.contains("more_setting",Qt::CaseInsensitive))
        {
            this->json_more_setting_=new JsonMoreSetting();
        }
        else if(key.contains("environment_setting",Qt::CaseInsensitive))
        {
            this->json_environment_setting_=new JsonEnvironmentSetting();
        }
    }
}

JsonType &JsonType::Instance(const QString &json_file_index_path)
{
    static JsonType instance(json_file_index_path);
    return instance;
}

JsonType::JsonType(const QString &json_file_index_path)
{
    if(json_file_index_path.isEmpty())
    {
        emit ResourceLoadingError();
        return;
    }

    QJsonObject json_object=FileReadSystem::GetInstance().ReadJsonFileToJsonObject(json_file_index_path);

    ParseJsonObject(json_object);
}

}
