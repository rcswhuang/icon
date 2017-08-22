#include "hiconpieitem.h"
#include "hpropertydlg.h"
#include "hiconapi.h"
#include <QObject>
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>
HIconPieItem::HIconPieItem(HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent)
{

}

HIconPieItem::HIconPieItem(const QRectF &rectF, HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent),rectF(rectF)
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pPieObj = NULL;
    bSelected = false;
}

QRectF HIconPieItem::boundingRect() const
{
    return shape().controlPointRect();
}

bool HIconPieItem::contains(const QPointF &point) const
{
    return shape().boundingRect().contains(point);
}

void HIconPieItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF mainRectF = rect();
    QRectF drawRectF = mainRectF;

    QColor penClr = QColor(pPieObj->getLineColorName()); //线条颜色
    int penWidth = pPieObj->getLineWidth();//线条宽度
    Qt::PenStyle penStyle = pPieObj->getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = pPieObj->getLineCapStyle(); //线条角度

    bool bFrameSee = pPieObj->getFrameSee();//边框可见
    quint8 nFillWay = pPieObj->getFillWay();//填充选择
    quint8 nFillStyle = pPieObj->getFillStyle(); //填充风格
    quint8 nTransparency = pPieObj->getTransparency(); //透明度
    //quint8 nFillDir = pRectObj->getFillDirection();//填充方向
    QColor fillClr = QColor(pPieObj->getFillColorName());//填充颜色
    //quint8 nFillPercentage = pRectObj->getFillPercentage(); //填充比例
    qreal fRotateAngle = pPieObj->getRotateAngle();
    painter->save();

    QPointF centerPoint = boundingRect().center();
    setTransformOriginPoint(centerPoint);
    QTransform transform;
    transform.rotate(fRotateAngle);
    setTransform(transform);

    QPen pen = QPen(penClr);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    pen.setCapStyle(capStyle);
    if(bFrameSee)
        painter->setPen(pen);
    else
        painter->setPen(Qt::NoPen);

    int startAngle = pPieObj->getStartAngle()*16;
    int spanAngle = pPieObj->getSpanAngle()*16;

    QBrush brush = QBrush(Qt::NoBrush);
    if(nFillWay >= 1)
    {
        painter->setOpacity(1-(qreal)nTransparency/100.00);
        Qt::BrushStyle bs = (Qt::BrushStyle)nFillStyle;
        //QBrush brush1(fillClr,bs);
        //brush = brush1;
        brush.setColor(fillClr);
        brush.setStyle(bs);
    }
    painter->setBrush(brush);

    painter->drawPie(rect(),startAngle,spanAngle);
    painter->restore();

    if(isSelected())
    {
        painter->save();
        QPen pen1 = QPen(Qt::green);
        pen1.setWidth(1);
        painter->setPen(pen1);
        qreal halfpw = 14.00;
        QRectF rect1,rect2,rect3,rect4;
        rect1.setSize(QSizeF(halfpw,halfpw));
        rect1.moveCenter(rect().topLeft());
        rect2.setSize(QSizeF(halfpw,halfpw));
        rect2.moveCenter(rect().topRight());
        rect3.setSize(QSizeF(halfpw,halfpw));
        rect3.moveCenter(rect().bottomLeft());
        rect4.setSize(QSizeF(halfpw,halfpw));
        rect4.moveCenter(rect().bottomRight());

        painter->drawRect(rect1);
        painter->drawRect(rect2);
        painter->drawRect(rect3);
        painter->drawRect(rect4);

        painter->restore();
    }
}

QPainterPath HIconPieItem::shape() const
{
    QPainterPath path;// = QGraphicsLineItem::shape();
    QRectF rectPath;
    rectPath.setX(rect().x() - 10);
    rectPath.setY(rect().y() - 10);
    rectPath.setWidth(rect().width() + 20);
    rectPath.setHeight(rect().height() + 20);
    path.addRect(rectPath);
    return path;

}

int HIconPieItem::type() const
{
    return enumPie;
}



void HIconPieItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pointStart = event->scenePos();
    pointLocation = pointInRect(pointStart);
    bSelected = true;
    HIconGraphicsItem::mousePressEvent(event);
}

void HIconPieItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal fRotateAngle = pPieObj->getRotateAngle();
    QTransform transform;
    transform.rotate(-fRotateAngle);
    QPointF pt = transform.map(event->scenePos()) - transform.map(pointStart);
    transform.rotate(fRotateAngle);

    pointStart = event->scenePos();
    bool bShift = false;
    if(event->modifiers() == Qt::ShiftModifier)
        bShift = true;

    if(pointLocation == 1)
    {
        QRectF rectNew;
        rectNew.setTopLeft(QPointF(rect().left() + pt.x(),rect().top() + pt.y()));
        rectNew.setBottomRight(rect().bottomRight());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 2)
    {
        QRectF rectNew;
        rectNew.setTopRight(QPointF(rect().right() + pt.x(),rect().top() + pt.y()));
        rectNew.setBottomLeft(rect().bottomLeft());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 3)
    {
        QRectF rectNew;
        rectNew.setBottomLeft(QPointF(rect().left() + pt.x(),rect().bottom() + pt.y()));
        rectNew.setTopRight(rect().topRight());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 4)
    {
        QRectF rectNew;
        rectNew.setBottomRight(QPointF(rect().right() + pt.x(),rect().bottom() + pt.y()));
        rectNew.setTopLeft(rect().topLeft());
        setRect(rectNew.normalized());
    }
    else
    {
        pPieObj->setModify(true);
        HIconGraphicsItem::mouseMoveEvent(event);
    }
}


void HIconPieItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //bSelected = false;

    HIconGraphicsItem::mouseReleaseEvent(event);
}

void HIconPieItem::keyPressEvent(QKeyEvent *event)
{
    int nStep = 5;
    if(event->modifiers() == Qt::ShiftModifier)
    {
        nStep = 1;
    }
    int ndx = 0;
    int ndy = 0;
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        ndx = 0;
        ndy = -nStep;
        break;
    }
    case Qt::Key_Down:
    {
        ndx = 0;
        ndy = nStep;
        break;
    }
    case Qt::Key_Left:
    {
        ndx = -nStep;
        ndy = 0;
        break;
    }
    case Qt::Key_Right:
    {
        ndx = nStep;
        ndy = 0;
        break;
    }
    }
    if(ndx == 0 && ndy == 0)
        return;
    QRectF newRect = rect().adjusted(ndx,ndy,ndx,ndy);
    setRect(newRect);
}

void HIconPieItem::setRect(const QRectF& rect)
{
    if(rect == rectF) return;
    prepareGeometryChange();
    rectF = rect;
    refreshBaseObj();
    update();
}

QRectF HIconPieItem::rect()const
{
    return rectF;
}

void HIconPieItem::setItemObj(HBaseObj *pObj)
{
    pPieObj = (HPieObj*)pObj;
}

HBaseObj* HIconPieItem::getItemObj()
{
    if(pPieObj)
        return pPieObj;
    return NULL;
}

void HIconPieItem::moveItemBy(qreal dx, qreal dy)
{
    QRectF newRectF;
    newRectF = rect().translated(dx,dy);
    setRect(newRectF);
}

void HIconPieItem::resizeItem(const QPolygonF& polygonF)
{
    if(polygonF.size() != 2)
        return;
    //topleft bottomright
    QRectF newRectF(polygonF.at(0),polygonF.at(1));
    setRect(newRectF);
}

void HIconPieItem::refreshBaseObj()
{
    pPieObj->topLeft = mapToScene(rect().topLeft());
    pPieObj->rectWidth = rect().width();
    pPieObj->rectHeight = rect().height();
    QPointF p = mapToScene(rect().center());
    pPieObj->setOX(p.x());
    pPieObj->setOY(p.y());
    pPieObj->setModify(true);
}

void HIconPieItem::setItemCursor(int location)
{
    if(location == 1 || location == 4)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else if(location == 2 || location == 3)
        setCursor(QCursor(Qt::SizeBDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}

ushort HIconPieItem::pointInRect(QPointF& point)
{
    qreal halfpw = 14.00;
    QRectF rect1,rect2,rect3,rect4;
    rect1.setSize(QSizeF(halfpw,halfpw));
    rect1.moveCenter(mapToScene(rect().topLeft()));
    rect2.setSize(QSizeF(halfpw,halfpw));
    rect2.moveCenter(mapToScene(rect().topRight()));
    rect3.setSize(QSizeF(halfpw,halfpw));
    rect3.moveCenter(mapToScene(rect().bottomLeft()));
    rect4.setSize(QSizeF(halfpw,halfpw));
    rect4.moveCenter(mapToScene(rect().bottomRight()));

    ushort location = 0;
    if(rect1.contains(point))
        location = 1;
    else if(rect2.contains(point))
        location = 2;
    else if(rect3.contains(point))
        location = 3;
    else if(rect4.contains(point))
        location = 4;
    else
        location = 0;
    return location;
}
