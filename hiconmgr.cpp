﻿#include "hiconmgr.h"

HIconMgr::HIconMgr()
    :bShowGrid(true),bShowCenterLine(true)
{
    pIconFrame = new HIconFrame(this);
    //pIconFrame->setIconMgr(this);
    pIconDocument = new HIconDocument(this);
    pIconState = new HIconState(this);
    bShowGrid = true;
    bShowCenterLine = true;
    strBgClr = "#FFFFFF";
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


void HIconMgr::New(const QString &catalogName, const int &nIconType)
{
    pIconDocument->New(catalogName,nIconType);
}

void HIconMgr::Del(const QString& catalogName,const int& nIconType,const QString& uuid)
{
    pIconDocument->Del(catalogName,nIconType,uuid);
}











