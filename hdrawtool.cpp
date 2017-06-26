#include "hdrawtool.h"
#include "hiconstate.h"
HDrawTool::HDrawTool(HIconState* iconState,DRAWSHAPE drawShape,const QString& iconName,const QString& iconType,const QString& uuid)
    :pIconState(iconState),enDrawShape(drawShape),strIconName(iconName),strIconType(iconType),strUuid(uuid)
{

}

HDrawTool::~HDrawTool()
{

}

void HDrawTool::clear()
{

}

void HDrawTool::OnEvent(HEvent &e)
{
    if(!e.event)
    {
        return;
    }
}
