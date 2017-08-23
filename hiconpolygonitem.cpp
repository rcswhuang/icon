#include "hiconpolygonitem.h"
#include <math.h>
#include "hpropertydlg.h"
#include <QObject>
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

HIconPolygonItem::HIconPolygonItem(HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent)
{

}

HIconPolygonItem::HIconPolygonItem(const QPolygonF &polygonF, HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent),pyVector(polygonF)
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pPolygonObj = new HPolygonObj();
}

QRectF HIconPolygonItem::boundingRect() const
{
    return shape().controlPointRect();
}

bool HIconPolygonItem::contains(const QPointF &point) const
{
    return shape().boundingRect().contains(point);
}

void HIconPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor penClr = QColor(pPolygonObj->getLineColorName()); //线条颜色
    int penWidth = pPolygonObj->getLineWidth();//线条宽度
    Qt::PenStyle penStyle = pPolygonObj->getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = pPolygonObj->getLineCapStyle(); //线条角度

    bool bFrameSee = pPolygonObj->getFrameSee();//边框可见
/*    quint8 nFillWay = pPolygonObj->getFillWay();//填充选择
    quint8 nFillStyle = pPolygonObj->getFillStyle(); //填充风格
    quint8 nTransparency = pPolygonObj->getTransparency(); //透明度
    quint8 nFillDir = pPolygonObj->getFillDirection();//填充方向
    QColor fillClr = QColor(pPolygonObj->getFillColorName());//填充颜色
    quint8 nFillPercentage = pPolygonObj->getFillPercentage(); //填充比例
    */
    painter->save();
    QPen pen = QPen(penClr);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    pen.setCapStyle(capStyle);
    if(bFrameSee)
        painter->setPen(pen);
    else
        painter->setPen(Qt::NoPen);


    //QPolygonF tempPloygonF = polygon();
    //tempPloygonF.replace(tempPloygonF.last(),pointMove);

    painter->drawPolygon(polygon());
   // if(bStart)
     //   painter->drawLine(mapToScene(QPointF(0,0)),mapToScene(QPointF(100,100)));
    //else
    //    painter->drawLines(pyVector);
    //painter->drawPolygon(pyf);
    //需要判断nFillStyle 如果是linear的模式 就要考虑填充方向了
    //
    /*
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
       // qreal top = rect().top()*(float)(nFillPercentage/100.00);
       // drawRectF.setTop(top);
    }
    path.setFillRule(Qt::WindingFill);*/
    //painter->drawPath(path);
    painter->restore();
    //

    if(isSelected())
    {
        painter->save();
        QPen pen1 = QPen(Qt::green);
        pen1.setWidth(1);
        painter->setPen(pen1);
        qreal halfpw = 14.00;

        int nRect = polygon().size();
        QRectF *pRect = new QRectF[nRect];

        for(int i = 0 ; i < nRect; i++)
        {
            pRect[i].setSize(QSizeF(halfpw,halfpw));
            pRect[i].moveCenter(polygon().at(i));
            painter->drawRect(pRect[i]);
        }
        if(pRect)
        {
            delete[] pRect;
            pRect = NULL;
        }

        painter->restore();
    }
}

QPainterPath HIconPolygonItem::shape() const
{
    QPainterPath path;
    QPainterPathStroker ps;
    ps.setWidth(150);

    path.addPolygon(polygon());
    QPainterPath path1;
    QTransform transform;
    path1.addPolygon(ps.createStroke(path).toFillPolygon(transform));
    return path1;
}

int HIconPolygonItem::type() const
{
    return enumPolygon;
}


void HIconPolygonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
   // HPropertyDlg dlg(pRectObj);
   // dlg.exec();
}

void HIconPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // pyVector.append(event->scenePos());
    //pointLocation = pointInRect(event->scenePos());
    bStart = true;
    HIconGraphicsItem::mousePressEvent(event);
}

void HIconPolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos() - pointStart;
    //ushort location = pointInRect(event->scenePos());
    //qDebug()<<"location:"<<location;
    //pointStart = event->scenePos();
    bool bShift = false;
    if(event->modifiers() == Qt::ShiftModifier)
        bShift = true;

    pPolygonObj->moveBy(pt.x(),pt.y());
    HIconGraphicsItem::mouseMoveEvent(event);
}


void HIconPolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    bStart = false;
    HIconGraphicsItem::mouseReleaseEvent(event);
}

void HIconPolygonItem::keyPressEvent(QKeyEvent *event)
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
}

ushort HIconPolygonItem::pointInRect(QPointF& point)
{
    QPointF a = point;
    int b = 0;
    int c = 0;
  /*  qreal halfpw = 14.00;
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
    return location;*/
    return 0;
}

void HIconPolygonItem::setItemCursor(int location)
{
    if(location == 1 || location == 4)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else if(location == 2 || location == 3)
        setCursor(QCursor(Qt::SizeBDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}

void HIconPolygonItem::setPolygon(const QPolygonF & polygon)
{
    if(pyVector == polygon) return;
    prepareGeometryChange();
    pyVector = polygon;
    refreshBaseObj();
    update();
}

QPolygonF HIconPolygonItem::polygon() const
{
    return pyVector;
}

void HIconPolygonItem::refreshBaseObj()
{
    pPolygonObj->pylist.clear();
    foreach(QPointF pt,pyVector)
        pPolygonObj->pylist.append(mapToScene(pt));
    QPointF p = mapToScene(polygon().boundingRect().center());
    pPolygonObj->setOX(p.x());
    pPolygonObj->setOY(p.y());
    pPolygonObj->setModify(true);
}

void HIconPolygonItem::setItemObj(HBaseObj* pObj)
{
    pPolygonObj = (HPolygonObj*)pObj;
}

HBaseObj* HIconPolygonItem::getItemObj()
{
    if(pPolygonObj)
        return pPolygonObj;
    return NULL;
}

void HIconPolygonItem::moveItemBy(qreal dx,qreal dy)
{

}

void HIconPolygonItem::resizeItem(const QPolygonF& polygonF)
{

}
