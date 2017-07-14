#include "hiconsymbol.h"
#include "hiconapi.h"
#include "hiconshowpattern.h"
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
    strSymbolName = dom->attribute("SymbolName");
    usSymbolType = dom->attribute("ObjType").toUInt();
    //fWidth = dom->attribute("Width").toDouble();
    //fHeight = dom->attribute("Height").toDouble();
    //fTransparent = dom->attribute("Transparent").toDouble();
    //nFillStyle = dom->attribute("FillStyle").toInt();
    //nFillCent = dom->attribute("FillCent").toInt();
    //bFill = dom->attribute("bFill").toInt();
    //pFillColor = new QColor(dom->attribute("FillColor"));
    //strBackgroundPath = dom->attribute("BackImagePath");

    QDomElement objEle = dom->namedItem("DrawObj").toElement();
    bool bChild = objEle.attribute("bChildren").toInt();
    if(!bChild)
        return;
    //构建下面的元素对象
    QDomNode n = objEle.firstChild();
    int i = 0;
    for(;!n.isNull();n=n.nextSibling(),i++)
    {
        QDomElement e = n.toElement();
        int nType = e.attribute("ObjType").toInt();
        HBaseObj* obj = NULL;
        if(nType == OBJ_TYPE_LINE)
        {
            //obj = new
        }
        else if(nType == OBJ_TYPE_RECTANGLE)
        {

        }
        else if(nType == OBJ_TYPE_ELLIPSE)
        {

        }
        else if(nType == OBJ_TYPE_ARC)
        {

        }
        obj->readXml(&e);

    }
}

void HIconSymbol::writeXml(QDomElement *dom)
{

}

void HIconSymbol::addObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
    int objID = getObjID(pObj->getShapeType());
    pObj->setProperty("OBJID",QVariant(objID));
    QString strObjName = QString("%1_%2_%3").arg(pObj->TagName()).arg(pObj->getShapeType()).arg(objID);
    pObj->setProperty("Name",QVariant(strObjName));
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
int HIconSymbol::getObjID(int nObjType)
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

void HIconSymbol::setIconSymbolWidth(double width)
{
    //fWidth = width;
}

void HIconSymbol::setIconSymbolHeight(double height)
{
    //fHeight = height;
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
    pShowPatternVector.indexOf(pCurPattern);
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
