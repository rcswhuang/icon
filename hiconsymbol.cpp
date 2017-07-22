﻿#include "hiconsymbol.h"
#include "hiconapi.h"
#include "hiconshowpattern.h"
#include "hiconobj.h"
#include <QVariant>
HIconSymbol::HIconSymbol(QObject* parent):QObject(parent)
{
    usSymbolType = DEVICE_TYPE_ICONSYMBOL;
    nMaxPattern = 0;
    nCurPattern = 0;
    pCurPattern = NULL;
}

HIconSymbol::~HIconSymbol()
{
    while(!pShowPatternVector.isEmpty())
    {
        HIconShowPattern* pattern = (HIconShowPattern*)pShowPatternVector.takeFirst();
        if(pattern)
        {
            delete pattern;
            pattern = NULL;
        }
    }
    pShowPatternVector.clear();
}

void HIconSymbol::readXml(QDomElement* dom)
{
    if(dom->isNull())
        return;
    strSymbolName = dom->attribute("IconSymbolName");
    usSymbolType = dom->attribute("IconSymbolType").toUInt();

    QDomElement objEle = dom->namedItem("Children").toElement();
    QDomNode n = objEle.firstChild();
    QList<HBaseObj*> pTempList;
    for(int i = 0;!n.isNull();n=n.nextSibling(),i++)
    {
        QDomElement e = n.toElement();
        QString strTagName = e.tagName();
        HBaseObj* pObj = newObj(strTagName);
        if(!pObj) continue;
        pTempList.append(pObj);
        pObj->readXml(&e);
    }

    QDomElement spEle = dom->namedItem("ShowPatterns").toElement();
    //构建下面的元素对象
    n = spEle.firstChild();
    for(int i = 0;!n.isNull();n=n.nextSibling(),i++)
    {
        QDomElement e = n.toElement();
        if(e.tagName() != "ShowPattern") continue;

        HIconShowPattern* pattern = newPattern();
        if(!pattern)
        {
            delete pattern;
            pattern = NULL;
            continue;
        }
        pattern->strName = e.attribute("Name");
        pattern->strAlias = e.attribute("Alias");
        pattern->nPattern = e.attribute("PatternID").toInt();
        //pShowPatternVector.append(pattern);
    }
    updateShowPattern(pTempList);

    pTempList.clear();
    //还要刷新一下 把对应的Obj 放到showPattern下面
}

void HIconSymbol::writeXml(QDomElement *dom)
{
    if(!dom)
        return;
    dom->setAttribute("IconSymbolName",strSymbolName);
    dom->setAttribute("IconSymbolType",usSymbolType);


    //先创建所有子图元元素xml结构
    QDomElement childDom = dom->ownerDocument().createElement("Children");
    dom->appendChild(childDom);
    for(int i = 0; i < pShowPatternVector.size();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)pShowPatternVector[i];
        if(!pattern)continue;
        pattern->writeXml(&childDom);
    }


    //再创建显示方案的xml结构
    QDomElement patternDom = dom->ownerDocument().createElement("ShowPatterns");
    dom->appendChild(patternDom);
    for(int i = 0; i < pShowPatternVector.size();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)pShowPatternVector[i];
        if(!pattern)continue;
        QDomElement patternChildDom = dom->ownerDocument().createElement("ShowPattern");
        patternChildDom.setAttribute("Name",pattern->strName);
        patternChildDom.setAttribute("Alias",pattern->strAlias);
        patternChildDom.setAttribute("PatternID",pattern->nPattern);
        patternDom.appendChild(patternChildDom);
    }


}

HBaseObj* HIconSymbol::newObj(QString tagName)
{
    quint8 drawShape = enumNo;
    if(tagName == "Line")
        drawShape = enumLine;
    else if(tagName == "Rectangle")
        drawShape = enumRectangle;
    else if(tagName == "Ellipse")
        drawShape = enumEllipse;
    else if(tagName == "Arc")
        drawShape = enumArc;
    else if(tagName == "Pie")
        drawShape = enumPie;
    else if(tagName == "Text")
        drawShape = enumText;
    return newObj(drawShape);
}

HBaseObj* HIconSymbol::newObj(int nObjType)
{
    HBaseObj* pObj = NULL;
    if(nObjType == enumLine)
    {
        pObj = new HLineObj();
    }
    else if(nObjType == enumRectangle)
    {
        pObj = new HRectObj();
    }
    else if(nObjType == enumEllipse)
    {
        pObj = new HEllipseObj();
    }
    else if(nObjType == enumArc)
    {
        pObj = new HArcObj();
    }
    else if(nObjType == enumPie)
    {
        pObj = new HPieObj();
    }
    else if(nObjType == enumText)
    {
        pObj = new HTextObj();
    }
    pObj->setShapeType((DRAWSHAPE)nObjType);
    if(pObj)
    {
        int objID = getObjID();
        pObj->setObjID(objID);
    }
    return pObj;
}

void HIconSymbol::addObj(HBaseObj* pObj)
{
    if(!pObj)
        return;

    QString strObjName = QString("%1_%2_%3").arg(pObj->TagName()).arg(pObj->getShapeType()).arg(pObj->getObjID());
    pObj->setObjName(strObjName);
    HIconShowPattern* pSP = getCurrentPatternPtr();
    if(!pSP)
        return;
    pSP->addObj(pObj);
}

void HIconSymbol::delObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
    HIconShowPattern* pSP = getCurrentPatternPtr();
    if(!pSP)
        return;
    pSP->delObj(pObj);
}

//获取ObjID
int HIconSymbol::getObjID()
{
    int nObjID = 1;
    while(findObjID(nObjID))
        nObjID++;
    return nObjID;
}

bool HIconSymbol::findObjID(int nObjID)
{
    if(pShowPatternVector.count() == 0) return false;
    for(int i = 0;i < pShowPatternVector.count();i++)
    {
        HIconShowPattern* pattern = (HIconShowPattern*)pShowPatternVector[i];
        for(int j = 0; j < pattern->pObjList.count();j++)
        {
            HBaseObj* pObj = (HBaseObj*)pattern->pObjList[j];
            if(pObj && pObj->getObjID() == nObjID)
                return true;
        }
    }
    return false;
}

void HIconSymbol::setSymbolName(const QString &strName)
{
    strSymbolName = strName;
}

QString HIconSymbol::getSymolName()
{
    return strSymbolName;
}

void HIconSymbol::setIconSymbolWidth(double width)
{
    //fWidth = width;
}

void HIconSymbol::setIconSymbolHeight(double height)
{
    //fHeight = height;
}

void HIconSymbol::updateShowPattern(QList<HBaseObj*> &list)
{
    foreach (HBaseObj* pObj, list) {
        HIconShowPattern* pattern = findPatternById(pObj->nPattern.at(0));
        if(!pattern) continue;
        pattern->addObj(pObj,false);
    }
}






bool HIconSymbol::PatterIsValid(int nId)
{
    if(nId < 0)
        return false;
    return true;
}

//新建
HIconShowPattern* HIconSymbol::newPattern(const QString& name)
{
    HIconShowPattern* newSP = new HIconShowPattern(this);
    newSP->strName = name;
    newSP->nPattern = nMaxPattern;
    nMaxPattern++;
    pShowPatternVector.append(newSP);
    setCurrentPatternPtr(newSP);
    return newSP;
}

HIconShowPattern* HIconSymbol::newPattern(int id)
{
    //if()
    HIconShowPattern* newSP = new HIconShowPattern(this);
    newSP->nPattern = id;
    pShowPatternVector.append(newSP);
    if(id >= nMaxPattern)
        nMaxPattern++;
    setCurrentPatternPtr(newSP);
    return newSP;
}

//删除
void HIconSymbol::delPattern(HIconShowPattern* sp)
{
    for(int i = 0; i< pShowPatternVector.size();i++)
    {
        HIconShowPattern* pPattern = pShowPatternVector.at(i);
        if(pPattern->nPattern == sp->nPattern)
        {
            pPattern->clear();
            pShowPatternVector.remove(i);
            delete pPattern;
            pPattern = NULL;
        }
    }
}

void HIconSymbol::delPattern(int id)
{
    for(int i = 0; i< pShowPatternVector.size();i++)
    {
        HIconShowPattern* pPattern = pShowPatternVector.at(i);
        if(pPattern->nPattern == id)
        {
            pPattern->clear();
            pShowPatternVector.remove(i);
            delete pPattern;
            pPattern = NULL;
        }
    }
}

void HIconSymbol::clearPattern()
{
    while (!pShowPatternVector.isEmpty()) {
        HIconShowPattern* pPattern = pShowPatternVector.takeFirst();
        pPattern->clear();
        delete pPattern;
        pPattern = NULL;
    }
}

//查找和设置
HIconShowPattern* HIconSymbol::findPatternById(int id)
{
    for(int i = 0; i< pShowPatternVector.size();i++)
    {
        HIconShowPattern* pPattern = pShowPatternVector.at(i);
        if(pPattern->nPattern == id)
            return pPattern;
    }
    return NULL;
}

void HIconSymbol::setCurrentPattern(int id)
{
    nCurPattern = id;
    setCurrentPatternPtr(findPatternById(id));
}

int HIconSymbol::getCurrentPattern()
{
    return nCurPattern;
}

int HIconSymbol::getCurrentPatternIndex()
{
    if(!pCurPattern || pShowPatternVector.isEmpty())
        return -1;
    return pShowPatternVector.indexOf(pCurPattern);
}

void HIconSymbol::setCurrentPatternPtr(HIconShowPattern* sp)
{
    pCurPattern = sp;
    nCurPattern = sp->nPattern;
}

HIconShowPattern* HIconSymbol::getCurrentPatternPtr()
{
    return pCurPattern;
}
