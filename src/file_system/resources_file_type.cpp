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
        return enum_map_.value(ResourcesType::kGLSL);
    else if(!s.compare("Images",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kImages);
    else if(!s.compare("Style",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kStyle);
    else if(!s.compare("Obj",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kObj);
    else if(!s.compare("Json",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kJson);
    else if(!s.compare("Model",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kModel);
    else if(!s.compare("Textures",Qt::CaseInsensitive))
        return enum_map_.value(ResourcesType::kTextures);

    return QString();
}

QString resourcesfiletype::ResourcesTypeToMapper::EnumToString(ResourcesType type) const
{
    switch(type)
    {
    case ResourcesType::kGLSL:
        return "GLSL";
    case ResourcesType::kImages:
        return "Images";
    case ResourcesType::kJson:
        return "Json";
    case ResourcesType::kStyle:
        return "Style";
    case ResourcesType::kObj:
        return "Obj";
    case ResourcesType::kModel:
        return "Model";
    case ResourcesType::kTextures:
        return "Textures";

    default:
        return QString();
    }
}

resourcesfiletype::ResourcesType resourcesfiletype::ResourcesTypeToMapper::StringToEnum(QString type) const
{
    if(!type.compare("GLSL",Qt::CaseInsensitive))
        return ResourcesType::kGLSL;
    else if(!type.compare("Images",Qt::CaseInsensitive))
        return ResourcesType::kImages;
    else if(!type.compare("Image",Qt::CaseInsensitive))
        return ResourcesType::kImages;
    else if(!type.compare("Style",Qt::CaseInsensitive))
        return ResourcesType::kStyle;
    else if(!type.compare("Obj",Qt::CaseInsensitive))
        return ResourcesType::kObj;
    else if(!type.compare("Json",Qt::CaseInsensitive))
        return ResourcesType::kJson;
    else if(!type.compare("Model",Qt::CaseInsensitive))
        return ResourcesType::kModel;
    else if(!type.compare("Textures",Qt::CaseInsensitive))
        return ResourcesType::kTextures;

    return ResourcesType::kNone;
}

resourcesfiletype::ResourcesTypeToMapper &resourcesfiletype::ResourcesTypeToMapper::Instance()
{
    static ResourcesTypeToMapper instance;
    return instance;
}

resourcesfiletype::ResourcesTypeToMapper::ResourcesTypeToMapper()
{
    enum_map_[ResourcesType::kImages]=":/images/";
    enum_map_[ResourcesType::kJson]=":/json/";
    enum_map_[ResourcesType::kGLSL]=":/GLSL/";
    enum_map_[ResourcesType::kStyle]=":/style/";
    enum_map_[ResourcesType::kObj]=":/objs/";
    enum_map_[ResourcesType::kModel]=":/model/";
    enum_map_[ResourcesType::kTextures]=":/textures/";
}
