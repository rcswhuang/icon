#include "hiconobjitem.h"

HIconObjItem::HIconObjItem(HBaseObj *obj,QGraphicsItem* parent)
    :pBaseObj(obj),QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
}

HIconObjItem::~HIconObjItem()
{

}

void HIconObjItem::setBaseObj(HBaseObj* obj)
{
    this->pBaseObj = obj;
}

HBaseObj* HIconObjItem::getBaseObj()
{
    return pBaseObj;
}

QRectF	HIconObjItem::boundingRect() const
{
   // if(pBaseObj)
    //    return pBaseObj->getBounding().adjusted(-5,-5,5,5);
    return QRectF();
}

void HIconObjItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //if(pBaseObj)
    //    pBaseObj->draw(painter);
}

QPainterPath HIconObjItem::shape() const
{
    //if(pBaseObj)
    //    return pBaseObj->getShape();
    return QPainterPath();
}

int	HIconObjItem::type() const
{
    return Type;
}

bool HIconObjItem::contains(const QPointF & point) const
{
    return false;
}

void HIconObjItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

QVariant HIconObjItem::itemChange(GraphicsItemChange change, const QVariant & value)
{

    return QGraphicsItem::itemChange(change,value);
}
