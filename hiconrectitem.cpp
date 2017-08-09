#include "hiconrectitem.h"
#include "hpropertydlg.h"
#include <qmath.h>
#include <QObject>
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>
HIconRectItem::HIconRectItem(HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent)
{

}

HIconRectItem::HIconRectItem(const QRectF &rectF, HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent),rectF(rectF)
{
    //pointLocation = LOCATIONNO;
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pRectObj = NULL;
   // QPointF centerPoint = rect().center();
    //setTransformOriginPoint(centerPoint);
}

QRectF HIconRectItem::boundingRect() const
{ 
    //return shape().boundingRect();
    qreal pw = 20;
    return QRectF(rect().x() - pw/2,rect().y() - pw/2,rect().width() + pw,rect().height()+pw);
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

    painter->drawRect(rect());
    //需要判断nFillStyle 如果是linear的模式 就要考虑填充方向了
    //

    QBrush brush;//(Qt::NoBrush);
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
    //painter->setBrush(brush);
    //painter->drawRect(rect());
    painter->fillRect(drawRectF,brush);
    //painter->restore();



    if(isSelected())
    {
       // painter->save();
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
    QPointF centerPoint = boundingRect().center();
    setTransformOriginPoint(centerPoint);
    setRotation(fRotateAngle);
}

QPainterPath HIconRectItem::shape() const
{
    QPainterPath path;// = QGraphicsLineItem::shape();
    QRectF rectPath;
    rectPath.setX(rect().x() - 10);
    rectPath.setY(rect().y() - 10);
    rectPath.setWidth(rect().width() + 20);
    rectPath.setHeight(rect().height() + 20);
    path.addRect(rectPath);
    /*QPainterPathStroker ps;
    ps.setWidth(20);
    path.moveTo(rect().topLeft());
    path.lineTo(rect().topRight());
    path.lineTo(rect().bottomRight());
    path.lineTo(rect().bottomLeft());
    path.lineTo(rect().topLeft());
    return ps.createStroke(path);*/
    return path;

}

int HIconRectItem::type() const
{
    return enumRectangle;
}


void HIconRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pointStart = event->scenePos();
    pointLocation = pointInRect(pointStart);
    HIconGraphicsItem::mousePressEvent(event);
}

void HIconRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos() - pointStart;

    qreal fRotateAngle = pRectObj->getRotateAngle();
    qreal deltaX = pt.x();//*qCos(fRotateAngle*PI/180.0) - pt.y()*qSin(fRotateAngle*PI/180.0);//*cosx;
    qreal deltaY = pt.y();//*qCos(fRotateAngle*PI/180.0) + pt.x()*qSin(fRotateAngle*PI/180.0);//*siny;


    pointStart = event->scenePos();
    bool bShift = false;
    if(event->modifiers() == Qt::ShiftModifier)
        bShift = true;
    prepareGeometryChange();

    if(pointLocation == 1)
    {
        QRectF rectNew;
        rectNew.setTopLeft(QPointF(rect().left() + deltaX,rect().top() + deltaY));
        rectNew.setBottomRight(rect().bottomRight());
        //setTransformOriginPoint(rectNew.center());
       // transform1.rotate(-pRectObj->getRotateAngle());
       // setTransform(transform1);
        //rectNew = transform1.mapRect(rectNew);
        setRect(rectNew.normalized());///
    }
    else if(pointLocation == 2)
    {
        QRectF rectNew;
        rectNew.setTopRight(QPointF(rect().right() + deltaX,rect().top() + deltaY));
        rectNew.setBottomLeft(rect().bottomLeft());

        setRect(rectNew.normalized());
        //QPointF centerPoint = boundingRect().center();
        //setTransformOriginPoint(centerPoint);
    }
    else if(pointLocation == 3)
    {
        QRectF rectNew;
        rectNew.setBottomLeft(QPointF(rect().left() + deltaX,rect().bottom() + deltaY));
        rectNew.setTopRight(rect().topRight());
        setTransformOriginPoint(rectNew.center());
        setRect(rectNew.normalized());
        //QPointF centerPoint = boundingRect().center();
        //setTransformOriginPoint(centerPoint);
    }
    else if(pointLocation == 4)
    {
       /* QRectF rectNew = rect();
        QPointF p1 = rect().topLeft();
        QPointF p2 = rect().topRight();
        QPointF p3 = rect().bottomLeft();
        QPointF p4 = rect().bottomRight();

        QTransform trans1 = transform();
        trans1.translate(rectNew.center().x(),rectNew.center().y());
        trans1.rotate(fRotateAngle*PI/180.0);
        setTransform(trans1);
        QRectF rect1 = trans1.mapRect(rect());
        QPointF p11 = rect1.topLeft();
        QPointF p12 = rect1.topRight();
        QPointF p13 = rect1.bottomLeft();
        QPointF p14 = rect1.bottomRight();



        QTransform trans2 = trans1.rotate(-fRotateAngle*PI/180.0);
        setTransform(trans2);
        QRectF rect2 = trans2.mapRect(rect1);
        rectNew.setBottomRight(QPointF(rect().right() + deltaX,rect().bottom() + deltaY));
        rectNew.setTopLeft(rect().topLeft());

        QPointF p21 = rect1.topLeft();
        QPointF p22 = rect1.topRight();
        QPointF p23 = rect1.bottomLeft();
        QPointF p24 = rect1.bottomRight();


        setRect(rectNew.normalized());


        //QPointF centerPoint = boundingRect().center();
        setTransformOriginPoint(rectNew.center());*/
        QRectF rectNew;
        rectNew.setBottomRight(QPointF(rect().right() + pt.x(),rect().bottom() + pt.y()));
        rectNew.setTopLeft(rect().topLeft());
        setRect(rectNew.normalized());
    }
    else
    {

        HIconGraphicsItem::mouseMoveEvent(event);
    }
}


void HIconRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos();

    HIconGraphicsItem::mouseReleaseEvent(event);
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

void HIconRectItem::setRect(const QRectF& rect)
{
    if(rect == rectF) return;
    prepareGeometryChange();
    rectF = rect;
    refreshBaseObj();
    update();
}

QRectF HIconRectItem::rect()const
{
    return rectF;
}

void HIconRectItem::setItemObj(HBaseObj *pObj)
{
    pRectObj = (HRectObj*)pObj;
}

HBaseObj* HIconRectItem::getItemObj()
{
    if(pRectObj)
        return pRectObj;
    return NULL;
}

void HIconRectItem::moveItemBy(qreal dx, qreal dy)
{
    QRectF newRectF;
    newRectF = rect().translated(dx,dy);
    setRect(newRectF);
}

void HIconRectItem::resizeItem(const QPolygonF& polygonF)
{
    if(polygonF.size() != 4)
        return;
    //topleft bottomright
    QRectF newRectF(polygonF.at(0),polygonF.at(3));
    setRect(newRectF);
}

void HIconRectItem::refreshBaseObj()
{
    pRectObj->topLeft = mapToScene(rect().topLeft());
    pRectObj->rectWidth = rect().width();
    pRectObj->rectHeight = rect().height();
    QPointF p = mapToScene(rect().center());
    pRectObj->setOX(p.x());
    pRectObj->setOY(p.y());
}

void HIconRectItem::setItemCursor(int location)
{
    if(location == 1 || location == 4)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else if(location == 2 || location == 3)
        setCursor(QCursor(Qt::SizeBDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}

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
