#include "hicondocument.h"
#include <QDir>
#include <QProcessEnvironment>
#include <QMessageBox>
HIconDocument::HIconDocument(HIconMgr* iconMgr):pIconMgr(iconMgr)
{
    pCurIconTemplate = NULL;
}

void HIconDocument::loadIconDoucument()
{
    //先找路径，在找文件夹，然后文件夹里面搜索添加完成
    QString iconsPath  = QString(qgetenv("wfsystem_dir"));
#ifdef WIN32
    iconsPath = QProcessEnvironment::systemEnvironment().value("wfsystem_dir");
#else
    iconsPath = "/users/huangw";
#endif
    iconsPath.append("/icons");

    QDir dirIconsPath(iconsPath);
    if(!dirIconsPath.exists())
        return;
    QFileInfoList iconsFileInfoList = dirIconsPath.entryInfoList(QDir::Dirs  | QDir::NoDotAndDotDot);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        if(info.isFile())continue;
        QString strChildFilePath = iconsPath + "/" + info.fileName();
        loadIconTemplateFile(strChildFilePath);

    }
}

void HIconDocument::loadIconTemplateFile(QString strIconsPath)//加载所有的模板文件
{
    //先找路径，在找文件夹，然后文件夹里面搜索添加完成
    QDir dirIconsFilePath(strIconsPath);
    if(!dirIconsFilePath.exists())
        return;
    QStringList filters;
    filters<<"*.xic";
    dirIconsFilePath.setNameFilters(filters);
    QFileInfoList iconsFileInfoList = dirIconsFilePath.entryInfoList(QDir::Files);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        if(!info.isFile())continue;
        QString strIconTemplateFile = strIconsPath + "/" + info.fileName();
        QUuid uuid = QUuid(info.fileName());
        HIconTemplate *pIconTemplate = new HIconTemplate(uuid);
        if(!pIconTemplate) continue;
        pIconTemplate->readXml(strIconTemplateFile);
        pIconTemplateList.append(pIconTemplate);
    }
}


void HIconDocument::saveIconDoucument()
{
    QString iconsPath = QString(getenv("wfsystem_dir"));;
#ifdef WIN32
    iconsPath = QProcessEnvironment::systemEnvironment().value("wfsystem_dir");
#else
    iconsPath = "/users/huangw";
#endif
    iconsPath.append("/icons");
    QDir dirIconsPath(iconsPath);
    if(!dirIconsPath.exists())
        dirIconsPath.mkdir(iconsPath);
    QFileInfoList iconsFileInfoList = dirIconsPath.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo info,iconsFileInfoList)
    {
        if(info.isFile())continue;
        saveIconTemplateFile(iconsPath,info.fileName());

    }
}

void HIconDocument::saveIconTemplateFile(const QString& strIconsPath,const QString& strFolderName)//保存所有的模板文件
{
    QDir dirIconsFilePath(strIconsPath);
    if(!dirIconsFilePath.exists())
        return;
    QString strIconsFolderPath = strIconsPath + "/" + strFolderName;
    for(int i = 0; i < pIconTemplateList.count();i++)
    {
        HIconTemplate* iconTemplate = pIconTemplateList[i];
        if(!iconTemplate) continue;
        if(IsIconInFolder(strFolderName,iconTemplate->getIconTypeId()))
        {
            QString strFileName = strIconsFolderPath + "/" + iconTemplate->getUuid().toString() + ".xic";
            iconTemplate->writeXml(strFileName);

        }
    }
}


bool HIconDocument::IsIconInFolder(const QString& strFolderName,const quint8& nIconType)
{
    bool bIn = false;
    if((strFolderName == "digital"||strFolderName == QStringLiteral("遥信")) && nIconType == TEMPLATE_TYPE_DIGITAL)
        bIn = true;
    return bIn;
}

void HIconDocument::initIconType()
{



}

HIconTemplate* HIconDocument::getCurrentTemplate()
{
    return pCurIconTemplate;
}

//遥信  红绿灯遥信  TEMPLATE_DIGITAL_
void HIconDocument::New(const QString& strIconTypeName,const QString &strTemplateName,int nTemplateType)
{
    //新建新的文件
    pCurIconTemplate = new HIconTemplate("");
    pCurIconTemplate->setIconTypeName(strIconTypeName);//普通开关
    pCurIconTemplate->setIconTypeId(nTemplateType);//遥信类
    pCurIconTemplate->getSymbol()->setSymbolName(strTemplateName);
    //pIconTemplateList.append(pCurIconTemplate);
}

void HIconDocument::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return;
        if(pIconTemplate->getIconTypeId() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
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
    if(pTemplate && pTemplate->getSymbol()->getSymolName() == strTemplateName)
    {
        //先删除原来的临时模板文件
        if(!pCurIconTemplate)
        {
            delete pCurIconTemplate;
            pCurIconTemplate = NULL;
        }
        //构建一个新的模板文件，然后把当前的模板文件拷贝给它
        pCurIconTemplate = new HIconTemplate;
        pTemplate->copyTo(pCurIconTemplate);
    }
    else
        pCurIconTemplate = NULL;

}

bool HIconDocument::Save()
{
    if(!pCurIconTemplate)
        return false;


    saveIconDoucument();
    return true;
}

HIconTemplate* HIconDocument::findIconTemplateByTemplateName(const QString& strTemplateName)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(pIconTemplate && pIconTemplate->getSymbol()->getSymolName() == strTemplateName)

            return pIconTemplate;

    }
    return NULL;
}


HIconTemplate* HIconDocument::findIconTemplateByTypeAndUuid(int nTemplateType, const QString &strUuid)
{
    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return NULL;
        if(pIconTemplate->getIconTypeId() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            return pIconTemplate;
        }
    }
    return NULL;
}
