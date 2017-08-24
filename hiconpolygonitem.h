#ifndef HICONPOLYGONITEM_H
#define HICONPOLYGONITEM_H

#include <QtGlobal>
#include "hiconapi.h"
#include "hicongraphicsitem.h"
class HBaseObj;
class HPolygonObj;
class QObject;
class QRectF;
class QPainterPath;
class QPointF;
class QPainter;
class QStyleOptionGraphicsItem;
class QKeyEvent;
class QGraphicsSceneMouseEvent;
class QPolygonF;
#include <QVector>


class HIconPolygonItem : public HIconGraphicsItem
{
public:
    enum {Type = enumEllipse};
    HIconPolygonItem(HIconGraphicsItem *parent = Q_NULLPTR);
    HIconPolygonItem(const QPolygonF &polygonF, HIconGraphicsItem *parent = Q_NULLPTR);
public:
    virtual void setPolygon(const QPolygonF & polygon);
    QPolygonF	polygon() const;
    void refreshBaseObj();
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
    virtual ushort pointInRect(QPointF& point);
    virtual void setItemCursor(int position);
    virtual void setItemObj(HBaseObj*);
    virtual HBaseObj* getItemObj();
    virtual void moveItemBy(qreal dx,qreal dy);
    virtual void resizeItem(const QPolygonF& polygonF);

public:
    HPolygonObj* pPolygonObj;
    ushort rectMode;
    ushort pointLocation;
    QPolygonF pyVector;
    QPointF pointStart;
};

#endif // HICONPOLYGONITEM_H
