﻿#ifndef HICONCOMMAND_H
#define HICONCOMMAND_H
/*
 * 撤销、删除类
*/
#include <QUndoCommand>
#include <QPolygonF>ß
class HIconMgr;
class HBaseObj;
class HIconCommand : public QUndoCommand
{
public:
    enum Type{
        New = 0,            //新建
        Delete = 1,         //删除
        Paste = 2,          //粘贴
        Move = 3,           //移动
        Group = 4,          //组合
        UnGroup = 5,        //解除
        Rotate = 6,         //旋转
        Turn = 7,           //翻转
        Resize = 8,         //改变大小
        PatternSwitch = 9   //显示方案切换
    };

    HIconCommand(HIconMgr* iconMgr);
    ~HIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HIconMgr* pIconMgr;
    bool bFirstTime;
};


//新建
class HNewIconCommand : public HIconCommand
{
public:
    HNewIconCommand(HIconMgr* iconMgr,HBaseObj* pObj);
    ~HNewIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HBaseObj* pObj;
};


//删除
class HDelIconCommand : public HIconCommand
{
public:
    HDelIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs);
    ~HDelIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
};


//粘贴
class HPasteIconCommand : public HIconCommand
{
public:
    HPasteIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs);
    ~HPasteIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;
};

//移动
class HMoveIconCommand : public HIconCommand
{
public:
    HMoveIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,qreal dx,qreal dy);
    HMoveIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<qreal> dxs,QList<qreal> dys);
    HMoveIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<QPointF> oldPt,QList<QPointF> newPt);
    ~HMoveIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;

    QList<qreal> dxList;

    QList<qreal> dyList;
};

//旋转
class HRotateIconCommand : public HIconCommand
{
public:
    HRotateIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,int angle);
    HRotateIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<int> angles);
    ~HRotateIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;

    QList<int> angleList;

};


//翻转
class HTurnIconCommand : public HIconCommand
{
public:
    HTurnIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,bool direction);
    ~HTurnIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;

    bool bDirection;

};

//改变大小
class HResizeIconCommand : public HIconCommand
{
public:
    HResizeIconCommand(HIconMgr* iconMgr,QList<HBaseObj*> pObjs,QList<QPolygonF> oldPts,QList<QPolygonF> newPts);
    ~HResizeIconCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    QList<HBaseObj*> pObjList;

    QList<QPolygonF> oldPtList;

    QList<QPolygonF> newPtList;

};
#endif // HICONCOMMAND_H
