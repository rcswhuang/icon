#include "hiconshowpattern.h"
#include "hiconlineitem.h"
#include "hiconobj.h"
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
    pObj->setShowPattern(this);
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
}

bool HIconShowPattern::equalPatternId(int nPatternId)
{
    if(nPattern == nPatternId)
        return true;
    else
        return false;
}

void HIconShowPattern::setObjItemVisible(int nPatternId)
{
    if(!pSymbol)
        return;
    for(int i = 0; i < pObjList.count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)pObjList.at(i);
        if(pObj )
        {
            if(pObj->getShapeType() == enumLine)
            {
                HLineObj* pLineObj = (HLineObj*)pObj;
                HIconLineItem* pItem = (HIconLineItem*)(pLineObj->getIconLineItem());
                if(pItem)
                {
                    if(equalPatternId(nPatternId))
                        pItem->setVisible(true);
                    else
                        pItem->setVisible(false);
                }
            }
        }
    }
}







