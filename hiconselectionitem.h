#ifndef HICONSELECTIONITEM_H
#define HICONSELECTIONITEM_H

#include <QtGlobal>
#include "hicongraphicsitem.h"
#include "hiconapi.h"
class QObject;
class QRectF;
class QPainterPath;
class QPointF;
class QPainter;
class QStyleOptionGraphicsItem;
class QKeyEvent;
class QGraphicsSceneMouseEvent;
class HIconSelectionItem : public HIconGraphicsItem
{
public:
    enum {Type = enumSelection};

    HIconSelectionItem(HIconGraphicsItem *parent = Q_NULLPTR);
    HIconSelectionItem(const QRectF &rectF, HIconGraphicsItem *parent = Q_NULLPTR);
public:
    void setRect(const QRectF& rect);
    QRectF rect()const;
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QPainterPath shape() const;
    virtual int type() const;
 //   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
 //   virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
 //   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    QRectF rectF;
    QPointF pointStart;
  //  bool bSelected;
};

#endif // HICONSELECTIONITEM_H
