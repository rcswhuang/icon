#include "hiconshowpattern.h"

HIconShowPattern::HIconShowPattern(HIconSymbol* symbol):pSymbol(symbol)
{

}

HIconShowPattern::~HIconShowPattern()
{

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
}
