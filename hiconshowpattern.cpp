#include "hiconshowpattern.h"
#include "hiconlineitem.h"
#include "hiconobj.h"
HIconShowPattern::HIconShowPattern(HIconSymbol* symbol):pSymbol(symbol)
{

}

HIconShowPattern::~HIconShowPattern()
{
    clear();
}

void HIconShowPattern::readXml(QDomElement* dom)
{
    if(!dom) return;

    QDomElement objEle = dom->namedItem("ShowPatterns").toElement();
    //构建下面的元素对象
    QDomNode n = objEle.firstChild();
    int i = 0;
    for(;!n.isNull();n=n.nextSibling(),i++)
    {
        QDomElement e = n.toElement();
        int patternID = e.attribute("PatternID").toInt();
        HIconShowPattern* pattern = pSymbol->newPattern(patternID);
        if(!pattern)
        {
            delete pattern;
            pattern = NULL;
            continue;
        }
        pattern->readXml(&e);
        pSymbol->pShowPatternVector.append(pattern);
    }
}

void HIconShowPattern::writeXml(QDomElement *dom)
{
    if(!dom) return;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)pObjList[i];
        QDomElement childEle = dom->ownerDocument().createElement(pObj->TagName());
        dom->appendChild(childEle);
        pObj->writeXml(&childEle);

    }
}

void HIconShowPattern::addObj(HBaseObj* pObj,bool badd)
{
    if(!pObj)
        return;
    if(badd)
        pObj->nPattern.append(nPattern);
    pObjList.append(pObj);
}

void HIconShowPattern::delObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
    pObjList.removeOne(pObj);
    delete pObj;
    pObj = NULL;
}

void HIconShowPattern::copyTo(HIconShowPattern* sp)
{
    if(!sp)
        return;
    sp->strName = strName;
    sp->nPattern = nPattern;
    sp->strAlias = strAlias;
    sp->pSymbol = pSymbol;
}

void HIconShowPattern::clear()
{
    if(pObjList.isEmpty()) return;
    while(!pObjList.isEmpty())
    {
        HBaseObj* pObj = pObjList.takeFirst();
        if(pObj)
        {
            delete pObj;
            pObj = NULL;
        }
    }
    pObjList.clear();
}







