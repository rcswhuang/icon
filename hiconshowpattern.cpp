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

}

void HIconShowPattern::writeXml(QDomElement *dom)
{

}

void HIconShowPattern::addObj(HBaseObj* pObj)
{
    if(!pObj)
        return;
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







