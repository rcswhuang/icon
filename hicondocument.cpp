#include "hicondocument.h"
#include <QDir>
#include <QProcessEnvironment>
#include <QMessageBox>
HIconDocument::HIconDocument(HIconMgr* iconMgr):pIconMgr(iconMgr)
{
    pCurIconTemplate = new HIconTemplate("0000");
}

HIconDocument::~HIconDocument()
{
    if(pCurIconTemplate)
    {
        delete pCurIconTemplate;
        pCurIconTemplate = NULL;
    }
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
    //获取遥信，遥测，遥调等文件夹
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
        if(IsIconInFolder(strFolderName,iconTemplate->getCatalogType()))
        {
            QString strFileName = strIconsFolderPath + "/" + iconTemplate->getUuid().toString() + ".xic";
            //如果有文件存在 就删除
            if(QFile::exists(strFileName))
            {
                QFile::remove(strFileName);
            }
            iconTemplate->writeXml(strFileName);

        }
    }
}


bool HIconDocument::IsIconInFolder(const QString& strFolderName,const quint8& nIconType)
{
    bool bIn = false;
    if((strFolderName == "digital"||strFolderName == QStringLiteral("遥信")) && nIconType == TEMPLATE_TYPE_DIGITAL)
        bIn = true;
    else if((strFolderName == "analogue"||strFolderName == QStringLiteral("遥测")) && nIconType == TEMPLATE_TYPE_ANALOGUE)
        bIn = true;
    else if((strFolderName == "yk"||strFolderName == QStringLiteral("遥控")) && nIconType == TEMPLATE_TYPE_YK)
        bIn = true;
    else if((strFolderName == "pluse"||strFolderName == QStringLiteral("遥脉")) && nIconType == TEMPLATE_TYPE_PLUSE)
        bIn = true;
    else if((strFolderName == "tap"||strFolderName == QStringLiteral("档位")) && nIconType == TEMPLATE_TYPE_TAP)
        bIn = true;
    else if((strFolderName == "light"||strFolderName == QStringLiteral("光字牌")) && nIconType == TEMPLATE_TYPE_LIGHT)
        bIn = true;
    else if((strFolderName == "jdpai"||strFolderName == QStringLiteral("接地牌")) && nIconType == TEMPLATE_TYPE_JDPAI)
        bIn = true;
    return bIn;
}

QString HIconDocument::getIconFolder(int nType)
{
    QString strFolderName;
    if(nType == TEMPLATE_TYPE_DIGITAL)
            strFolderName = QStringLiteral("遥信");
    else if(nType == TEMPLATE_TYPE_ANALOGUE)
            strFolderName = QStringLiteral("遥测");
    else if(nType == TEMPLATE_TYPE_YK)
            strFolderName =QStringLiteral("遥控");
    else if( nType == TEMPLATE_TYPE_PLUSE)
        strFolderName = QStringLiteral("遥脉");
    else if(nType == TEMPLATE_TYPE_TAP)
        strFolderName = QStringLiteral("档位");
    else if(nType == TEMPLATE_TYPE_LIGHT)
        strFolderName = QStringLiteral("光字牌");
    else if(nType == TEMPLATE_TYPE_JDPAI)
        strFolderName = QStringLiteral("接地牌");

    return strFolderName;
}

HIconTemplate* HIconDocument::getCurrentTemplate()
{
    return pCurIconTemplate;
}


void HIconDocument::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    if(pCurIconTemplate)
    {
        pCurIconTemplate->clear();
    }

    HIconTemplate *pTemplate = new HIconTemplate("");
    pTemplate->setCatalogName(strCatalogName);//普通开关
    pTemplate->setCatalogType(nCatalogType);//遥信类
    pTemplate->getSymbol()->setSymbolName(strTemplateName);
    pTemplate->getSymbol()->newPattern(QStringLiteral("缺省"));
    pIconTemplateList.append(pTemplate);

    pTemplate->copyTo(pCurIconTemplate);
}

void HIconDocument::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    QString iconsPath = QString(getenv("wfsystem_dir"));;
#ifdef WIN32
    iconsPath = QProcessEnvironment::systemEnvironment().value("wfsystem_dir");
#else
    iconsPath = "/users/huangw";
#endif
    iconsPath.append("/icons");
    if(pCurIconTemplate->getCatalogType() == nTemplateType && pCurIconTemplate->getUuid().toString() == strUuid)
    {
        pCurIconTemplate->clear();
    }

    for(int i = 0; i < pIconTemplateList.size();i++)
    {
        HIconTemplate* pIconTemplate = (HIconTemplate*)pIconTemplateList.at(i);
        if(!pIconTemplate)
            return;
        if(pIconTemplate->getCatalogType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            QString strFileName = iconsPath + "/" + getIconFolder(pIconTemplate->getCatalogType())+ "/" +pIconTemplate->getUuid().toString() + ".xic";
            if(QFile::exists(strFileName))
            {
                QFile::remove(strFileName);
            }
            pIconTemplateList.removeOne(pIconTemplate);
            delete pIconTemplate;
            pIconTemplate = NULL;
        }
    }
}

void HIconDocument::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!pCurIconTemplate)
    {
        return;
    }

    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(nTemplateType,strUuid);
    if(pTemplate && pTemplate->getSymbol()->getSymolName() == strTemplateName)
    {
        pCurIconTemplate->clear();
        pTemplate->copyTo(pCurIconTemplate);
    }
}

bool HIconDocument::Save(bool savefile)
{
    if(!pCurIconTemplate)
    {
        return false;
    }

    HIconTemplate* pTemplate = findIconTemplateByTypeAndUuid(pCurIconTemplate->getCatalogType(),pCurIconTemplate->getUuid().toString());
    if(pTemplate)
    {
        pTemplate->clear();
        pCurIconTemplate->copyTo(pTemplate);
        pTemplate->setModify(false);
    }

    if(savefile)
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
        if(pIconTemplate->getCatalogType() == nTemplateType && pIconTemplate->getUuid().toString() == strUuid)
        {
            return pIconTemplate;
        }
    }
    return NULL;
}
