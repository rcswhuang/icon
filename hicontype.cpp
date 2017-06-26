#include "hicontype.h"

HIconType::HIconType()
{

}

void HIconType::setIconTypeName(const QString &strName)
{
    strIconTypeName = strName;
}

QString HIconType::getIconTypeName()
{
    return strIconTypeName;
}

void HIconType::setIconType(int type)
{
    nIconType = type;
}

int HIconType::getIconType()
{
    return nIconType;
}

void HIconType::setParentType(int pType)
{
    nParentType = pType;
}

int HIconType::getParentType()
{
    return nParentType;
}
