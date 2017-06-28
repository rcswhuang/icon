#include "hiconrectitem.h"
#include "hpropertydlg.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <qmath.h>
#include <QDebug>
HIconRectItem::HIconRectItem(QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{

}

HIconRectItem::HIconRectItem(const QRectF &rectF, QGraphicsRectItem *parent)
    :QGraphicsRectItem(rectF,parent)
{
    //pointLocation = LOCATIONNO;
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pRectObj = new HRectObj();
    setRotation(0);
}

QRectF HIconRectItem::boundingRect() const
{ 
    return shape().controlPointRect();
}

bool HIconRectItem::contains(const QPointF &point) const
{
    return shape().boundingRect().contains(point);
}

void HIconRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF mainRectF = rect();
    QRectF drawRectF = mainRectF;

    QColor penClr = QColor(pRectObj->getLineColorName()); //线条颜色
    int penWidth = pRectObj->getLineWidth();//线条宽度
    Qt::PenStyle penStyle = pRectObj->getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = pRectObj->getLineCapStyle(); //线条角度

    bool bFrameSee = pRectObj->getFrameSee();//边框可见
    quint8 nFillWay = pRectObj->getFillWay();//填充选择
    quint8 nFillStyle = pRectObj->getFillStyle(); //填充风格
    quint8 nTransparency = pRectObj->getTransparency(); //透明度
    quint8 nFillDir = pRectObj->getFillDirection();//填充方向
    QColor fillClr = QColor(pRectObj->getFillColorName());//填充颜色
    quint8 nFillPercentage = pRectObj->getFillPercentage(); //填充比例
    qreal fRotateAngle = pRectObj->getRotateAngle();
    painter->save();
    QPen pen = QPen(penClr);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    pen.setCapStyle(capStyle);
    if(bFrameSee)
        painter->setPen(pen);
    else
        painter->setPen(Qt::NoPen);

    //painter->drawRect(rect());
    //需要判断nFillStyle 如果是linear的模式 就要考虑填充方向了
    //


    QBrush brush(Qt::NoBrush);
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
            //painter->setBrush(brush2);
            //painter->drawRect(rect());
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
            //painter->setBrush(brush);
        }
        qreal top = rect().top()*(float)(nFillPercentage/100.00);
        drawRectF.setTop(top);
    }
    painter->setBrush(brush);
    painter->drawRect(rect());
    //painter->fillRect(drawRectF,brush);
    //painter->restore();
    //


    if(isSelected())
    {
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


    }
    painter->restore();
    setRotation(fRotateAngle);
}

QPainterPath HIconRectItem::shape() const
{
    QPainterPath path;// = QGraphicsLineItem::shape();
   /* QRectF rectPath;
    rectPath.setX(rect().x() - 10);
    rectPath.setY(rect().y() - 10);
    rectPath.setWidth(rect().width() + 20);
    rectPath.setHeight(rect().height() + 20);
    path.addRect(rectPath);*/
    QPainterPathStroker ps;
    ps.setWidth(20);
    path.moveTo(rect().topLeft());
    path.lineTo(rect().topRight());
    path.lineTo(rect().bottomRight());
    path.lineTo(rect().bottomLeft());
    path.lineTo(rect().topLeft());
    return ps.createStroke(path);
    return path;

}

int HIconRectItem::type() const
{
    return enumRectangle;
}


void HIconRectItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    HPropertyDlg dlg(pRectObj);
    dlg.exec();
}

void HIconRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pointStart = event->scenePos();
    //QPointF pointF = mouseEvent->scenePos();
    pointLocation = pointInRect(pointStart);
    QGraphicsRectItem::mousePressEvent(event);
}

void HIconRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos() - pointStart;
    //qreal fRotageAngle = rotation();
    //qreal rad = qRadiansToDegrees(qTan(event->scenePos().x()/event->scenePos().y()));
   // qreal cosx = qCos(45 - fRotageAngle);
    //qreal siny = qSin(45 - fRotageAngle);
    qreal deltaX = pt.x();//*cosx;
    qreal deltaY = pt.y();//*siny;
    pointStart = event->scenePos();
    bool bShift = false;
    if(event->modifiers() == Qt::ShiftModifier)
        bShift = true;
    if(pointLocation == 1)
    {
        QRectF rectNew;
        rectNew.setTopLeft(QPointF(rect().left() + deltaX,rect().top() + deltaY));
        rectNew.setBottomRight(rect().bottomRight());
        setRect(rectNew.normalized());///
    }
    else if(pointLocation == 2)
    {
        QRectF rectNew;
        rectNew.setTopRight(QPointF(rect().right() + deltaX,rect().top() + deltaY));
        rectNew.setBottomLeft(rect().bottomLeft());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 3)
    {
        QRectF rectNew;
        rectNew.setBottomLeft(QPointF(rect().left() + deltaX,rect().bottom() + deltaY));
        rectNew.setTopRight(rect().topRight());
        setRect(rectNew.normalized());
    }
    else if(pointLocation == 4)
    {
        QRectF rectNew;
        rectNew.setBottomRight(QPointF(rect().right() + deltaX,rect().bottom() + deltaY));
        rectNew.setTopLeft(rect().topLeft());
        setRect(rectNew.normalized());
    }
    else
    {

        QGraphicsRectItem::mouseMoveEvent(event);
    }
}


void HIconRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pRectObj->topLeft = mapToScene(rect().topLeft());
    pRectObj->rectWidth = rect().width();
    pRectObj->rectHeight = rect().height();
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void HIconRectItem::keyPressEvent(QKeyEvent *event)
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

/*
QVariant HIconRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{

}
*/
ushort HIconRectItem::pointInRect(QPointF& point)
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
