#include "hicondocument.h"

HIconDocument::HIconDocument(HIconMgr* iconMgr):pIconMgr(iconMgr)
{
    pCurIconTemplate = NULL;
}

void HIconDocument::initIconType()
{



}


HIconTemplate* HIconDocument::getCurrentTemplate()
{
    return pCurIconTemplate;
}

void HIconDocument::New(const QString &strTemplateName,int nTemplateType)
{
    //按照名字查找一下，如果存在，就不在新建

    //如果当前图符文件有修改且未保存，提示进行保存

    //新建新的文件
    pCurIconTemplate = new HIconTemplate;
    pCurIconTemplate->setAttrName(strTemplateName);//普通开关
    pCurIconTemplate->setIconType(nTemplateType);//遥信类
    pIconTemplateList.append(pCurIconTemplate);
    //for(int i=0;i<pCurIconTemplate->getSymbol()->
}

void HIconDocument::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return;
        if(pIconTemplate->getIconType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            pIconTemplateList.removeOne(pIconTemplate);
            delete pIconTemplate;
            pIconTemplate = NULL;
        }
    }
}

void HIconDocument::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(nTemplateType,strUuid);
    if(pTemplate && pTemplate->getAttrName() == strTemplateName)
        pCurIconTemplate = pTemplate;
    else
        pCurIconTemplate = NULL;

}

bool HIconDocument::Save()
{
    if(!pCurIconTemplate)
        return false;
    //pCurIconTemplate->writeXml();
    return true;
}


HIconTemplate* HIconDocument::findIconTemplateByTypeAndUuid(int nTemplateType, const QString &strUuid)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return NULL;
        if(pIconTemplate->getIconType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            return pIconTemplate;
        }
    }
    return NULL;
}
