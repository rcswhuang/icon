#ifndef HICONLINEITEM_H
#define HICONLINEITEM_H

#include <QtGlobal>
#include "hiconapi.h"
#include "hicongraphicsitem.h"
class HBaseObj;
class HLineObj;
class QObject;
class QRectF;
class QPainterPath;
class QPointF;
class QPainter;
class QStyleOptionGraphicsItem;
class QKeyEvent;
class QGraphicsSceneMouseEvent;
class QPolygonF;

class HIconLineItem : public HIconGraphicsItem
{
public:
    enum {Type = enumLine};
    enum
    {
        LineNo,
        LineMove,
        LineSize
    };
    enum
    {
        LOCATIONNO,
        LOCATIONLEFT,
        LOCATIONRIGHT
    };
    HIconLineItem(HIconGraphicsItem *parent = Q_NULLPTR);
    HIconLineItem(const QLineF &line, HIconGraphicsItem *parent = Q_NULLPTR);
public:
    QLineF line() const;
    void setLine(const QLineF& lineF);
    void refreshBaseObj();
    void resizeItem(const QPolygonF& polygonF);
public:
    virtual QRectF boundingRect() const;
    virtual bool contains(const QPointF &point) const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QPainterPath shape() const;
    virtual int type() const;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
public:
    virtual ushort pointInRect(QPointF& point);
    virtual void setItemCursor(int position);
    virtual void setItemObj(HBaseObj*);
    virtual HBaseObj* getItemObj();
    virtual void moveItemBy(qreal dx, qreal dy);
public:
    QLineF lineF;
    HLineObj* pLineObj;
    ushort lineMode;
    bool bSelected;

private:
    ushort pointLocation;
    QPointF curPointF;
    QPointF startPointF;
    QPointF endPointF;

};

#endif // QICONLINEITEM_H
