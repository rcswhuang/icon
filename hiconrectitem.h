#ifndef HICONRECTITEM_H
#define HICONRECTITEM_H

#include <QGraphicsRectItem>
#include "iconapi.h"
#include "hiconobj.h"
class HIconRectItem : public QGraphicsRectItem
{
public:
    enum {Type = enumRectangle};
    enum
    {

    };
    enum
    {
        LOCATIONNO,
        LOCATIONLEFT,
        LOCATIONRIGHT
    };
    HIconRectItem(QGraphicsRectItem *parent = Q_NULLPTR);
    HIconRectItem(const QRectF &rectF, QGraphicsRectItem *parent = Q_NULLPTR);

public:
    virtual QRectF boundingRect() const;
    virtual bool contains(const QPointF &point) const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QPainterPath shape() const;
    virtual int type() const;

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);


  //  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);*/
public:
    ushort pointInRect(QPointF& point);

public:
   // HLineObj* pLineObj;
    HRectObj* pRectObj;
    ushort rectMode;
    ushort pointLocation;
    QPointF pointStart;
  //  bool bSelected;
};

#endif // HICONRECTITEM_H
