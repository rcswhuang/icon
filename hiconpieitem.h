#ifndef HICONPIEITEM_H
#define HICONPIEITEM_H

#include <QtGlobal>
#include "hiconapi.h"
#include "hicongraphicsitem.h"
class HBaseObj;
class HPieObj;
class QObject;
class QRectF;
class QPainterPath;
class QPointF;
class QPainter;
class QStyleOptionGraphicsItem;
class QKeyEvent;
class QGraphicsSceneMouseEvent;

class HIconPieItem :public HIconGraphicsItem
{
public:
    enum {Type = enumPie};
    HIconPieItem(HIconGraphicsItem *parent = Q_NULLPTR);
    HIconPieItem(const QRectF &rectF, HIconGraphicsItem *parent = Q_NULLPTR);
public:
    void setRect(const QRectF& rect);
    QRectF rect()const;
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
    virtual HBaseObj* getItemObj();
    virtual void setItemObj(HBaseObj*);
public:
    QRectF rectF;
    bool bSelected;
    HPieObj* pPieObj;
    ushort rectMode;
    ushort pointLocation;
    QPointF pointStart;
};

#endif // HICONPIEITEM_H
