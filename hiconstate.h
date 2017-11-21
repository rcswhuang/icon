#ifndef HICONSTATE_H
#define HICONSTATE_H
#include <QObject>
#include <QPainterPath>
#include "hiconapi.h"
#include "hbaseobj.h"
#include "hiconmgr.h"

class HIconMgr;
class HIconState
{
public:
    HIconState(HIconMgr* pMgr);
    ~HIconState();

    void setDrawShape(DRAWSHAPE drawShape){curDrawShape = drawShape;}
    DRAWSHAPE getDrawShape(){return curDrawShape;}
     void appendObj(HBaseObj* obj);

public:
    DRAWSHAPE curDrawShape;//当前绘制对象
    HIconMgr* pIconMgr;
};

#endif // HICONSTATE_H
