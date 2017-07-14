#ifndef HICONSTATE_H
#define HICONSTATE_H
#include "hdrawtool.h"
#include "hiconapi.h"
#include "hevent.h"
#include <QPainterPath>
#include "hbaseobj.h"
#include "hiconmgr.h"

#include <QObject>
class HIconMgr;
struct Path
{
    QPainterPath painterPath;
    QPen pen;
    QBrush brush;
    bool deviceCoord;
};

class HIconState
{
public:
    HIconState(HIconMgr* pMgr);
    ~HIconState();
    bool findTool(DRAWSHAPE drawShape,const QString& strIconName = NULL, const QString& iconType = NULL,const QString& uuid = NULL);
    void OnEvent(HEvent& e);
    void OnDrawPath(const QList<Path>& pathList);
    void setDrawShape(DRAWSHAPE drawShape){curDrawShape = drawShape;}
    DRAWSHAPE getDrawShape(){return curDrawShape;}
    void selectTool(DRAWSHAPE drawShape,const QString& strIconName = NULL, const QString& iconType = NULL,const QString& uuid = NULL);
    void appendObj(HBaseObj* obj);
    HDrawTool* getCurTool(){return pCurTool;}
 //  void drawPath(const QList<Path>& pathList);
signals:
    //void drawPath(const QList<Path>& pathList);
public:
    HDrawTool* pCurTool;//当前绘制工具
    DRAWSHAPE curDrawShape;//当前绘制对象
    QList<HDrawTool*> drawToolList;

    HIconMgr* pIconMgr;
};

#endif // HICONSTATE_H
