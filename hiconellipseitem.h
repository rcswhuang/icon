#ifndef HICONELLIPSEITEM_H
#define HICONELLIPSEITEM_H

#include <QGraphicsEllipseItem>
#include "iconapi.h"
#include "hiconobj.h"

class HIconEllipseItem : public QGraphicsEllipseItem
{
public:
    enum {Type = enumEllipse};
    HIconEllipseItem(QGraphicsRectItem *parent = Q_NULLPTR);
    HIconEllipseItem(const QRectF &rectF, QGraphicsRectItem *parent = Q_NULLPTR);

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
    HEllipseObj* pEllipseObj;
    ushort rectMode;
    ushort pointLocation;
    QPointF pointStart;
};

#endif // HICONELLIPSEITEM_H
