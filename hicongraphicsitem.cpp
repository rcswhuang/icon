﻿#include "hicongraphicsitem.h"
#include <QRectF>
HIconGraphicsItem::HIconGraphicsItem(QGraphicsItem* parent):QGraphicsItem(parent)
{

}

HIconGraphicsItem::~HIconGraphicsItem()
{

}

QRectF HIconGraphicsItem::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void HIconGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //return QGraphicsItem::paint(painter,option,widget);
}

ushort HIconGraphicsItem::pointInRect(QPointF& point)
{
    return 0;
}

void HIconGraphicsItem::setItemCursor(int position)
{

}

void HIconGraphicsItem::setItemObj(HBaseObj * pObj)
{

}

HBaseObj* HIconGraphicsItem::getItemObj()
{
    return NULL;
}

bool HIconGraphicsItem::contains(const QPointF &point) const
{
    return false;
}

QPainterPath HIconGraphicsItem::shape() const
{
    return QPainterPath();
}

int HIconGraphicsItem::type() const
{
    return QGraphicsItem::type();
}

void HIconGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void HIconGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void HIconGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void HIconGraphicsItem::keyPressEvent(QKeyEvent *event)
{
    QGraphicsItem::keyPressEvent(event);
}

void HIconGraphicsItem::setRect(const QRectF& rect)
{

}

QRectF HIconGraphicsItem::rect()const
{
    return QRectF(0,0,0,0);
}

void HIconGraphicsItem::moveItemBy(qreal dx,qreal dy)
{

}


