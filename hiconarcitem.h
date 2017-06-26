﻿#ifndef HICONARCITEM_H
#define HICONARCITEM_H

#include <QGraphicsEllipseItem>
#include "iconapi.h"
#include "hiconobj.h"

class HIconArcItem : public QGraphicsEllipseItem
{
public:
    enum {Type = enumEllipse};
    HIconArcItem(QGraphicsRectItem *parent = Q_NULLPTR);
    HIconArcItem(const QRectF &rectF, QGraphicsRectItem *parent = Q_NULLPTR);

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
    bool bSelected;
    HArcObj* pArcObj;
    ushort rectMode;
    ushort pointLocation;
    QPointF pointStart;
};
#endif // HICONARCITEM_H
