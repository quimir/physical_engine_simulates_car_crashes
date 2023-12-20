#ifndef RESOURCES_FILE_TYPE_H
#define RESOURCES_FILE_TYPE_H

#include <QString>
#include <QMap>

namespace resourcesfiletype
{
/**
 * @brief The ResourcesType enum Type of resource file, now existing type by json, iamge, shader, style.
 */
enum ResourcesType
{
    Image,
    Json,
    Shader,
    Style
};

class ResourcesTypeToMapper
{
public:
    inline static ResourcesTypeToMapper& Instance()
    {
        static ResourcesTypeToMapper instance;
        return instance;
    }

    inline QString EnumToString(ResourcesType type)const
    {
        return enum_map_.value(type);
    }

private:
    inline ResourcesTypeToMapper()
    {
        enum_map_[Image]=":/image/";
        enum_map_[Json]=":/json/";
        enum_map_[Shader]=":/shader/";
        enum_map_[Style]=":/style/";
    }

    ResourcesTypeToMapper(const ResourcesTypeToMapper&) = delete;
    ResourcesTypeToMapper& operator=(const ResourcesTypeToMapper&) = delete;

private:
    QMap<ResourcesType,QString> enum_map_;
};
}

#endif // RESOURCES_FILE_TYPE_H
