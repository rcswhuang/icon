#include "hiconcircleitem.h"
#include "hpropertydlg.h"
#include <QObject>
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>
HIconCircleItem::HIconCircleItem(HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent)
{

}

HIconCircleItem::HIconCircleItem(const QRectF &rectF, HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent),rectF(rectF)
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pCircleObj = NULL;
}

QRectF HIconCircleItem::boundingRect() const
{
    return shape().controlPointRect();
}

bool HIconCircleItem::contains(const QPointF &point) const
{
    return shape().boundingRect().contains(point);
}

void HIconCircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF mainRectF = rect();
    QRectF drawRectF = mainRectF;

    QColor penClr = QColor(pCircleObj->getLineColorName()); //线条颜色
    int penWidth = pCircleObj->getLineWidth();//线条宽度
    Qt::PenStyle penStyle = pCircleObj->getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = pCircleObj->getLineCapStyle(); //线条角度

    bool bFrameSee = pCircleObj->getFrameSee();//边框可见
    quint8 nFillWay = pCircleObj->getFillWay();//填充选择
    quint8 nFillStyle = pCircleObj->getFillStyle(); //填充风格
    quint8 nTransparency = pCircleObj->getTransparency(); //透明度
    quint8 nFillDir = pCircleObj->getFillDirection();//填充方向
    QColor fillClr = QColor(pCircleObj->getFillColorName());//填充颜色
    //quint8 nFillPercentage = pEllipseObj->getFillPercentage(); //填充比例
    qreal fRotateAngle = pCircleObj->getRotateAngle();
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

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addEllipse(rect());
    painter->drawPath(path);


    QBrush brush;
    if(nFillWay >= 1)
    {
        painter->setOpacity(1-(qreal)nTransparency/100.00);
        if(nFillStyle == Qt::LinearGradientPattern)
        {
            QPointF ps1,ps2;
            switch(nFillDir)
            {
                case DIRECT_BOTTOM_TO_TOP:
                {
                    ps2 = rect().topLeft();
                    ps1 = rect().bottomLeft();
                    break;
                }
                case DIRECT_TOP_TO_BOTTOM: //有顶到底
                {
                    ps1 = rect().topLeft();
                    ps2 = rect().bottomLeft();
                    break;
                }
                case DIRECT_LEFT_TO_RIGHT: //由左到右
                {
                    ps1 = rect().topLeft();
                    ps2 = rect().topRight();
                    break;
                }
                case DIRECT_RIGHT_TO_LEFT: //由右到左
                {
                    ps1 = rect().topRight();
                    ps2 = rect().topLeft();
                    break;
                }
                case DIRECT_VER_TO_OUT: //垂直到外
                {
                    ps1 = QPointF(rect().center().x(),rect().top());
                    ps2 = rect().topLeft();
                    break;
                }
                case DIRECT_HORi_TO_OUT: //水平向外
                {
                    ps1 = QPointF(rect().left(),rect().center().y());
                    ps2 = rect().topLeft();
                    break;
                }
                case DIRECT_VER_TO_IN: //垂直向里
                {
                    ps2 = QPointF(rect().center().x(),rect().top());
                    ps1 = rect().topLeft();
                    break;
                }
                case DIRECT_HORI_TO_IN: //垂直向里
                {
                    ps2 = QPointF(rect().left(),rect().center().y());
                    ps1 = rect().topLeft();
                    break;
                }
            }
            QLinearGradient lgrd(ps1,ps2);
            lgrd.setColorAt(0.0,fillClr);
            lgrd.setColorAt(0.5,fillClr.lighter(150));
            lgrd.setColorAt(1.0,fillClr.lighter(250));
            lgrd.setSpread(QGradient::ReflectSpread);
            QBrush brush2(lgrd);
            brush = brush2;
        }
        else if(nFillStyle == Qt::RadialGradientPattern)
        {
            QRadialGradient lgrd(rect().center(),qMin(rect().width(),rect().height())/2);
            lgrd.setColorAt(0.0,fillClr);
            lgrd.setColorAt(0.5,fillClr.dark(150));
            lgrd.setColorAt(1.0,fillClr.dark(250));
            lgrd.setSpread(QGradient::ReflectSpread);
            QBrush brush2(lgrd);
            brush = brush2;
        }
        else if(nFillStyle == Qt::ConicalGradientPattern)
        {
            QConicalGradient lgrd(rect().center(),270);
            lgrd.setColorAt(0.0,fillClr);
            lgrd.setColorAt(0.5,fillClr.lighter(150));
            lgrd.setColorAt(1.0,fillClr.lighter(250));
            lgrd.setSpread(QGradient::ReflectSpread);
            QBrush brush2(lgrd);
            brush = brush2;
        }
        else
        {
            Qt::BrushStyle bs = (Qt::BrushStyle)nFillStyle;
            QBrush brush1(fillClr,bs);
            brush = brush1;
        }
        path.setFillRule(Qt::WindingFill);
        painter->setBrush(brush);
        painter->drawPath(path);

    }
    painter->restore();
    //

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

QPainterPath HIconCircleItem::shape() const
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

int HIconCircleItem::type() const
{
    return enumCircle;
}


void HIconCircleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pointStart = event->scenePos();
    pointLocation = pointInRect(pointStart);
    HIconGraphicsItem::mousePressEvent(event);
}

void HIconCircleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    qreal fRotateAngle = pCircleObj->getRotateAngle();
    QTransform transform;
    transform.rotate(-fRotateAngle);
    QPointF pt = transform.map(event->scenePos()) - transform.map(pointStart);
    transform.rotate(fRotateAngle);

    pointStart = event->scenePos();
    bool bShift = false;
    if(event->modifiers() == Qt::ShiftModifier)
        bShift = true;
    double delta = qMax(pt.x(),pt.y());
    if(pointLocation == 1)
    {
        QRectF rectNew;
        rectNew.setTopLeft(QPointF(rect().left() + delta,rect().top() + delta));
        rectNew.setBottomRight(rect().bottomRight());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 2)
    {
        QRectF rectNew;
        rectNew.setTopRight(QPointF(rect().right() + delta,rect().top() + delta));
        rectNew.setBottomLeft(rect().bottomLeft());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 3)
    {
        QRectF rectNew;
        rectNew.setBottomLeft(QPointF(rect().left() + delta,rect().bottom() + delta));
        rectNew.setTopRight(rect().topRight());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 4)
    {
        QRectF rectNew;
        rectNew.setBottomRight(QPointF(rect().right() + delta,rect().bottom() + delta));
        rectNew.setTopLeft(rect().topLeft());
        setRect(rectNew.normalized());
    }
    else
    {
        pCircleObj->moveBy(pt.x(),pt.y());
        HIconGraphicsItem::mouseMoveEvent(event);
    }
}


void HIconCircleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    HIconGraphicsItem::mouseReleaseEvent(event);
}

void HIconCircleItem::keyPressEvent(QKeyEvent *event)
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

void HIconCircleItem::setRect(const QRectF& rect)
{
    if(rect == rectF) return;
    prepareGeometryChange();
    rectF = rect;
    refreshBaseObj();
    update();
}

QRectF HIconCircleItem::rect()const
{
    return rectF;
}

void HIconCircleItem::setItemObj(HBaseObj *pObj)
{
    pCircleObj = (HCircleObj*)pObj;
}

HBaseObj* HIconCircleItem::getItemObj()
{
    if(pCircleObj)
        return pCircleObj;
    return NULL;
}

void HIconCircleItem::moveItemBy(qreal dx, qreal dy)
{
    QRectF newRectF;
    newRectF = rect().translated(dx,dy);
    setRect(newRectF);
}

void HIconCircleItem::resizeItem(const QPolygonF& polygonF)
{
    if(polygonF.size() != 2)
        return;
    QRectF newRectF(polygonF.at(0),polygonF.at(1));
    setRect(newRectF);
}

void HIconCircleItem::refreshBaseObj()
{
    pCircleObj->topLeft = mapToScene(rect().topLeft());
    pCircleObj->rectWidth = rect().width();
    pCircleObj->rectHeight = rect().height();
    QPointF p = mapToScene(rect().center());
    pCircleObj->setOX(p.x());
    pCircleObj->setOY(p.y());
    pCircleObj->setModify(true);
}

ushort HIconCircleItem::pointInRect(QPointF& point)
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

void HIconCircleItem::setItemCursor(int location)
{
    if(location == 1 || location == 4)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else if(location == 2 || location == 3)
        setCursor(QCursor(Qt::SizeBDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}


