#include "src_include/file_system/resources_file_type.h"

resourcesfiletype::ResourcesTypeToMapper &resourcesfiletype::ResourcesTypeToMapper::GetInstance()
{
    return Instance();
}

QString resourcesfiletype::ResourcesTypeToMapper::EnumToStringPath(ResourcesType type) const
{
    return enum_map_.value(type);
}

QString resourcesfiletype::ResourcesTypeToMapper::StringToEnumToStringPath(QString type) const
{
    QString s(type);
    if(!s.compare("GLSL",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::GLSL);
    else if(!s.compare("Image",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::Image);
    else if(!s.compare("Style",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::Style);
    else if(!s.compare("Obj",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::Obj);
    else if(!s.compare("Json",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::Json);

    return QString();
}

QString resourcesfiletype::ResourcesTypeToMapper::EnumToString(ResourcesType type) const
{
    switch(type)
    {
    case ResourcesType::GLSL:
        return "GLSL";
    case ResourcesType::Image:
        return "Image";
    case ResourcesType::Json:
        return "Json";
    case ResourcesType::Style:
        return "Style";
    case ResourcesType::Obj:
        return "Obj";

    default:
        return QString();
    }
}

resourcesfiletype::ResourcesTypeToMapper &resourcesfiletype::ResourcesTypeToMapper::Instance()
{
    static ResourcesTypeToMapper instance;
    return instance;
}

resourcesfiletype::ResourcesTypeToMapper::ResourcesTypeToMapper()
{
    enum_map_[ResourcesType::Image]=":/image/";
    enum_map_[ResourcesType::Json]=":/json/";
    enum_map_[ResourcesType::GLSL]=":/GLSL/";
    enum_map_[ResourcesType::Style]=":/style/";
    enum_map_[ResourcesType::Obj]=":/objs/";
}
