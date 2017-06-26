#ifndef HICONOBJITEM_H
#define HICONOBJITEM_H

#include <QObject>
#include <QGraphicsItem>
#include "hbaseobj.h"
class HIconObjItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum{Type = UserType + 1};
    HIconObjItem(HBaseObj *obj,QGraphicsItem* parent = 0);
    virtual ~HIconObjItem();

    void setBaseObj(HBaseObj* obj);
    HBaseObj* getBaseObj();
public:
    virtual QRectF	boundingRect() const;
    virtual void	paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual QPainterPath	shape() const;
    virtual int	type() const;
    virtual bool	contains(const QPointF & point) const;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

signals:

public slots:

private:
    HBaseObj* pBaseObj;
};

#endif // HICONOBJITEM_H
