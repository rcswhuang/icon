#include "hiconmgr.h"

HIconMgr::HIconMgr()
    :bShowGrid(true),bShowCenterLine(true)
{
    pIconFrame = new HIconFrame(this);
    //pIconFrame->setIconMgr(this);
    pIconDocument = new HIconDocument(this);
    pIconState = new HIconState(this);
    pIconUndoStack = new QUndoStack;
    bShowGrid = true;
    bShowCenterLine = true;
    strBgClr = "#FFFFFF";
}

HIconDocument* HIconMgr::getIconDocument()
{
    if(pIconDocument)
        return pIconDocument;
    return NULL;
}

HIconTemplate* HIconMgr::getIconTemplate()
{
    if(pIconDocument)
        return pIconDocument->getCurrentTemplate();
    return NULL;
}

HIconState* HIconMgr::getIconState()
{
    if(pIconState)
        return pIconState;
    return NULL;
}

HIconFrame* HIconMgr::getIconFrame()
{
    if(pIconFrame)
        return pIconFrame;
    return NULL;
}

QUndoStack* HIconMgr::getIconUndoStack()
{
    if(pIconUndoStack)
        return pIconUndoStack;
    return NULL;
}

void HIconMgr::setBackgroundColor(QString clrName)
{
    strBgClr = clrName;
}

QString HIconMgr::getBackgroundColor()
{
    return strBgClr;
}

void HIconMgr::setShowGrid(bool show)
{
    bShowGrid = show;
}

bool HIconMgr::getShowGrid()
{
    return bShowGrid;
}

void HIconMgr::setShowCenterLine(bool show)
{
    bShowCenterLine = show;
}

bool HIconMgr::getShowCenterLine()
{
    return bShowCenterLine;
}


void HIconMgr::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    pIconDocument->New(strTemplateName,strCatalogName,nCatalogType);
}

void HIconMgr::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    pIconDocument->Del(strTemplateName,nTemplateType,strUuid);
}

bool HIconMgr::Save(bool savefile)
{
    return pIconDocument->Save(savefile);
}

void HIconMgr::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    pIconDocument->Open(strTemplateName,nTemplateType,strUuid);
}








