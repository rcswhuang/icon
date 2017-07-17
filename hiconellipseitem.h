﻿#ifndef HICONELLIPSEITEM_H
#define HICONELLIPSEITEM_H

#include <QtGlobal>
#include "hiconapi.h"
#include "hicongraphicsitem.h"
class HBaseObj;
class HEllipseObj;
class QObject;
class QRectF;
class QPainterPath;
class QPointF;
class QPainter;
class QStyleOptionGraphicsItem;
class QKeyEvent;
class QGraphicsSceneMouseEvent;

class HIconEllipseItem : public HIconGraphicsItem
{
public:
    enum {Type = enumEllipse};
    HIconEllipseItem(HIconGraphicsItem *parent = Q_NULLPTR);
    HIconEllipseItem(const QRectF &rectF, HIconGraphicsItem *parent = Q_NULLPTR);
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
    virtual void setItemObj(HBaseObj*);
    virtual HBaseObj* getItemObj();
public:
    QRectF rectF;
    HEllipseObj* pEllipseObj;
    ushort rectMode;
    ushort pointLocation;
    QPointF pointStart;
};

#endif // HICONELLIPSEITEM_H
