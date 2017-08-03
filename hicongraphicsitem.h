#ifndef HICONGRAPHICSITEM_H
#define HICONGRAPHICSITEM_H
#include <QGraphicsItem>
#include "hiconcommand.h"
class QPointF;
class HBaseObj;
class QGraphicsItem;
class HIconGraphicsItem :public QGraphicsItem
{
public:
    HIconGraphicsItem(QGraphicsItem * parent = 0);
    ~HIconGraphicsItem();
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
    virtual void setRect(const QRectF& rect);
    virtual QRectF rect()const;
    virtual void setItemObj(HBaseObj*);
    virtual HBaseObj* getItemObj();
    virtual ushort pointInRect(QPointF& point);
    virtual void setItemCursor(int position);
    virtual void moveItemBy(qreal dx,qreal dy);
    virtual void resizeItem(const QPolygonF& polygonF);

};

#endif // HICONGRAPHICSITEM_H
