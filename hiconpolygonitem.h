#ifndef HICONPOLYGONITEM_H
#define HICONPOLYGONITEM_H

#include <QGraphicsPolygonItem>
#include "hiconapi.h"
#include "hiconobj.h"
#include <QVector>

class HIconPolygonItem : public QGraphicsPolygonItem
{
public:
    enum {Type = enumEllipse};
    HIconPolygonItem(QGraphicsPolygonItem *parent = Q_NULLPTR);
    HIconPolygonItem(const QPolygonF &polygonF, QGraphicsPolygonItem *parent = Q_NULLPTR);

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

public:
    ushort pointInRect(QPointF& point);

public:
    HPolygonObj* pPolygonObj;
    ushort rectMode;
    ushort pointLocation;
    QVector<QPointF> pyVector;
    bool bStart;
    QPointF pointMove;
    QPointF pointStart;
};

#endif // HICONPOLYGONITEM_H
