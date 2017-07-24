#include "hiconcommand.h"
#include "hiconapi.h"
#include "hbaseobj.h"
#include "hiconobj.h"
HIconCommand::HIconCommand(HIconMgr* iconMgr):pIconMgr(iconMgr)
{

}

HIconCommand::~HIconCommand()
{

}


int HIconCommand::id() const
{
    return -1;
}
void HIconCommand::redo()
{

}

void HIconCommand::undo()
{

}


////////////////////////////////////////新建///////////////////////////////////////////
HNewIconCommand::HNewIconCommand(HIconMgr* iconMgr,HBaseObj* obj):HIconCommand(iconMgr),pObj(obj)
{
    setText("create object");
}

HNewIconCommand::~HNewIconCommand()
{

}

int HNewIconCommand::id() const
{
    return New;
}

void HNewIconCommand::redo()
{
  //回复新建
}

void HNewIconCommand::undo()
{
//删除新建的
    pObj->setDeleted(true);
    //隐藏对应的item
}

////////////////////////////////////////删除///////////////////////////////////////////
HDelIconCommand::HDelIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> objs):HIconCommand(iconMgr),pObjList(objs)
{
    setText("create object");
}

HDelIconCommand::~HDelIconCommand()
{

}

int HDelIconCommand::id() const
{
    return Delete;
}

void HDelIconCommand::redo()
{

}

void HDelIconCommand::undo()
{

}


////////////////////////////////////////粘贴///////////////////////////////////////////
HPasteIconCommand::HPasteIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> objs):HIconCommand(iconMgr),pObjList(objs)
{
    setText("create object");
}

HPasteIconCommand::~HPasteIconCommand()
{

}

int HPasteIconCommand::id() const
{
    return Paste;
}

void HPasteIconCommand::redo()
{

}

void HPasteIconCommand::undo()
{

}


////////////////////////////////////////移动///////////////////////////////////////////
HMoveIconCommand::HMoveIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,qreal dx,qreal dy)
    :HIconCommand(iconMgr),pObjList(pObjs)
{
    for(int i = 0; i < pObjList.count();i++)
    {
        dxList.append(dx);
        dyList.append(dy);
    }
    setText("Move Object(s)");
}

HMoveIconCommand::HMoveIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<qreal> dxs,QList<qreal> dys)
    :HIconCommand(iconMgr),pObjList(pObjs),dxList(dxs),dyList(dys)
{
    setText("Move Object(s)");
}

HMoveIconCommand::HMoveIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<QPointF> oldPt,QList<QPointF> newPt)
    :HIconCommand(iconMgr),pObjList(pObjs)
{
    for(int i = 0; i< pObjList.count();i++)
    {
        dxList.append(newPt.at(i).x() - oldPt.at(i).x());
        dyList.append(newPt.at(i).y() - oldPt.at(i).y());
    }
    setText("Move Object(s)");
}

HMoveIconCommand::~HMoveIconCommand()
{

}

int HMoveIconCommand::id() const
{
    return Move;
}

void HMoveIconCommand::redo()
{

}

void HMoveIconCommand::undo()
{

}


////////////////////////////////////////旋转///////////////////////////////////////////
HRotateIconCommand::HRotateIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,int angle)
    :HIconCommand(iconMgr),pObjList(pObjs)
{
    for(int i = 0; i < pObjList.count();i++)
    {
        angleList.append(angle);
    }
    setText("rotate object");
}

HRotateIconCommand::HRotateIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<int> angles)
    :HIconCommand(iconMgr),pObjList(pObjs),angleList(angles)
{
    setText("rotate object");
}

HRotateIconCommand::~HRotateIconCommand()
{

}

int HRotateIconCommand::id() const
{
    return Rotate;
}

void HRotateIconCommand::redo()
{

}

void HRotateIconCommand::undo()
{

}


////////////////////////////////////////翻转///////////////////////////////////////////
HTurnIconCommand::HTurnIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> objs,bool direction )
    :HIconCommand(iconMgr),pObjList(objs),bDirection(direction)
{
    setText("turn object");
}

HTurnIconCommand::~HTurnIconCommand()
{

}

int HTurnIconCommand::id() const
{
    return Turn;
}

void HTurnIconCommand::redo()
{

}

void HTurnIconCommand::undo()
{

}


////////////////////////////////////////改变大小///////////////////////////////////////////
HResizeIconCommand::HResizeIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> objs,QList<QPolygonF> oldPts,QList<QPolygonF> newPts)
    :HIconCommand(iconMgr),pObjList(objs),oldPtList(oldPts),newPtList(newPts)
{
    setText("resize object");
}

HResizeIconCommand::~HResizeIconCommand()
{

}

int HResizeIconCommand::id() const
{
    return Resize;
}

void HResizeIconCommand::redo()
{

}

void HResizeIconCommand::undo()
{

}
