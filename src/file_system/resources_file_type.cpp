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
        return enum_map_.value(ResourcesType::kImage);
    else if(!s.compare("Style",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kStyle);
    else if(!s.compare("Obj",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kObj);
    else if(!s.compare("Json",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kJson);
    else if(!s.compare("Model",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kModel);

    return QString();
}

QString resourcesfiletype::ResourcesTypeToMapper::EnumToString(ResourcesType type) const
{
    switch(type)
    {
    case ResourcesType::GLSL:
        return "GLSL";
    case ResourcesType::kImage:
        return "Image";
    case ResourcesType::kJson:
        return "Json";
    case ResourcesType::kStyle:
        return "Style";
    case ResourcesType::kObj:
        return "Obj";
    case ResourcesType::kModel:
        return "Model";

    default:
        return QString();
    }
}

resourcesfiletype::ResourcesType resourcesfiletype::ResourcesTypeToMapper::StringToEnum(QString type) const
{
    if(!type.compare("GLSL",Qt::CaseInsensitive))
        return ResourcesType::GLSL;
    else if(!type.compare("Image",Qt::CaseInsensitive))
        return ResourcesType::kImage;
    else if(!type.compare("Style",Qt::CaseInsensitive))
        return ResourcesType::kStyle;
    else if(!type.compare("Obj",Qt::CaseInsensitive))
        return ResourcesType::kObj;
    else if(!type.compare("Json",Qt::CaseInsensitive))
        return ResourcesType::kJson;
    else if(!type.compare("Model",Qt::CaseInsensitive))
        return ResourcesType::kModel;

    return ResourcesType::kNone;
}

resourcesfiletype::ResourcesTypeToMapper &resourcesfiletype::ResourcesTypeToMapper::Instance()
{
    static ResourcesTypeToMapper instance;
    return instance;
}

resourcesfiletype::ResourcesTypeToMapper::ResourcesTypeToMapper()
{
    enum_map_[ResourcesType::kImage]=":/image/";
    enum_map_[ResourcesType::kJson]=":/json/";
    enum_map_[ResourcesType::GLSL]=":/GLSL/";
    enum_map_[ResourcesType::kStyle]=":/style/";
    enum_map_[ResourcesType::kObj]=":/objs/";
    enum_map_[ResourcesType::kModel]=":/model/";
}
