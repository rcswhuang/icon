#include "hiconstate.h"
#include "hiconobj.h"
HIconState::HIconState(HIconMgr* pMgr):pIconMgr(pMgr)
{
    pCurTool = NULL;
    curDrawShape = enumNo;
}

HIconState::~HIconState()
{

}

bool HIconState::findTool(DRAWSHAPE drawShape,const QString& strIconName, const QString& iconType,const QString& uuid)
{
    for(int i = 0; i < drawToolList.count();i++)
    {
        HDrawTool* pTool = (HDrawTool*)drawToolList.at(i);
        if(!pTool)
            continue;
        if(pTool->DrawShape() == drawShape)
        {
            pCurTool = pTool;
            return true;
        }
    }
    return false;
}

void HIconState::selectTool(DRAWSHAPE drawShape,const QString& strIconName, const QString& iconType,const QString& uuid)
{
    if(findTool(drawShape,strIconName,iconType,uuid))
        return;
    switch(drawShape)
    {
    case enumLine:
        {
            //pCurTool = new HLineTool(this,drawShape,strIconName,iconType,uuid);
           // drawToolList.append(pCurTool);
        }
    }
}


void HIconState::OnEvent(HEvent& e)
{
    if(pCurTool)
        pCurTool->OnEvent(e);
}

void HIconState::OnDrawPath(const QList<Path>& pathList)
{
    pIconMgr->getIconFrame()->drawPath(pathList);
}

void HIconState::appendObj(HBaseObj *obj)
{
    //模板里面增加
    if(pIconMgr && pIconMgr->getIconTemplate() && pIconMgr->getIconTemplate()->getSymbol())
        pIconMgr->getIconTemplate()->getSymbol()->addObj(obj);
}






