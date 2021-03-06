﻿#ifndef HICONFRAME_H
#define HICONFRAME_H
#include "hframe.h"
#include "hiconscene.h"
#include <QWidget>
#include <QRectF>
#include <QResizeEvent>
#include "hbaseobj.h"


class HIconMgr;
struct Path;
class HIconFrame : public HFrame
{
    Q_OBJECT
public:
    HIconFrame(QWidget * parent = 0, Qt::WindowFlags f = 0 );
    HIconFrame(HIconMgr* pMgr,QWidget * parent = 0, Qt::WindowFlags f = 0 );
    ~HIconFrame();

public:

    void setIconMgr(HIconMgr* iconmgr);

    //刷新选中点、选中框
    void refreshSelected(const QRectF& rect);

    //鼠标的改变
    void cursorChanged(const QCursor& cursor);

    //设置scene的逻辑区域
    void setLogicRect(QRectF& rectF);

    //在pattern获取Item对象
    HIconGraphicsItem* addItemByIconObj(HBaseObj* pObj);

    //增加scene的显示方案
    void refreshSceneByPatternId(int nPatternId);

    //删除scene的显示方案
    void clearSceneByPatternId(int nPatternId);

    //获取scene的区域
    QRectF getLogicRect();

    //获取frame里面的scene对象
    HIconScene* getIconScene();

    //设置显示方案对象的显示和隐藏功能
    void setItemVisible(int nPatternId);

    //获取item
    HIconGraphicsItem* getIconGraphicsItemByObj(HBaseObj* pObj);

protected:

    //事件过滤
   // virtual bool eventFilter( QObject *obj, QEvent *event);//过滤的对象，过滤的事件

private:
    QRectF m_sceneRect;
    HIconMgr* m_pIconMgr;

};

#endif // HICONFRAME_H
