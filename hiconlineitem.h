#ifndef HICONLINEITEM_H
#define HICONLINEITEM_H

#include <QGraphicsLineItem>
#include "iconapi.h"
class HLineObj;
class HIconLineItem : public QGraphicsLineItem
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
    HIconLineItem(QGraphicsItem *parent = Q_NULLPTR);
    HIconLineItem(const QLineF &line, QGraphicsItem *parent = Q_NULLPTR);

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
