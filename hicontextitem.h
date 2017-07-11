#ifndef HICONTEXTITEM_H
#define HICONTEXTITEM_H

/*
 * 没有采用QGraphicsTextItem而是采用QGraphicsRectItem来完成
*/
#include <QGraphicsRectItem>
#include "iconapi.h"
#include "hiconobj.h"
class HIconTextItem : public QGraphicsRectItem
{
public:
    enum {Type = enumText};
    enum
    {

    };
    enum
    {
        LOCATIONNO,
        LOCATIONLEFT,
        LOCATIONRIGHT
    };
    HIconTextItem(QGraphicsRectItem *parent = Q_NULLPTR);
    HIconTextItem(const QRectF &rectF, QGraphicsRectItem *parent = Q_NULLPTR);

public:
    virtual QRectF boundingRect() const;
    virtual bool contains(const QPointF &point) const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QPainterPath shape() const;
    virtual int type() const;

    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
public:
    ushort pointInRect(QPointF& point);
    void setItemCursor(int position);
public:
   // HLineObj* pLineObj;
    HTextObj* pTextObj;
    ushort rectMode;
    ushort pointLocation;
    QPointF pointStart;
  //  bool bSelected;
};


#endif // HICONTEXTITEM_H
