#include "hiconpolylineitem.h"
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

HIconPolylineItem::HIconPolylineItem(HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent)
{

}

HIconPolylineItem::HIconPolylineItem(const QPolygonF &polygonF, HIconGraphicsItem *parent)
    :HIconGraphicsItem(parent),pyVector(polygonF)
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pPolylineObj = new HPolylineObj();
}

QRectF HIconPolylineItem::boundingRect() const
{
    return shape().controlPointRect();
}

bool HIconPolylineItem::contains(const QPointF &point) const
{
    return shape().boundingRect().contains(point);
}

void HIconPolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor penClr = QColor(pPolylineObj->getLineColorName()); //线条颜色
    int penWidth = pPolylineObj->getLineWidth();//线条宽度
    Qt::PenStyle penStyle = pPolylineObj->getLineStyle(); //线条形状
    Qt::PenCapStyle capStyle = pPolylineObj->getLineCapStyle(); //线条角度

    bool bFrameSee = pPolylineObj->getFrameSee();//边框可见
    quint8 nFillWay = pPolylineObj->getFillWay();//填充选择
    quint8 nFillStyle = pPolylineObj->getFillStyle(); //填充风格
    quint8 nTransparency = pPolylineObj->getTransparency(); //透明度
    quint8 nFillDir = pPolylineObj->getFillDirection();//填充方向
    QColor fillClr = QColor(pPolylineObj->getFillColorName());//填充颜色
    quint8 nFillPercentage = pPolylineObj->getFillPercentage(); //填充比例
    qreal fRotateAngle = pPolylineObj->getRotateAngle();

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
    if(polygon().isClosed())
    {
        path.setFillRule(Qt::WindingFill);
        path.addPolygon(polygon());
        painter->drawPath(path);
    }
    else
    {
        path.moveTo(polygon().at(0));
        for(int i = 1; i < polygon().size();i++)
            path.lineTo(polygon().at(i));
        painter->drawPath(path);
    }

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
       // qreal top = rect().top()*(float)(nFillPercentage/100.00);
       // drawRectF.setTop(top);
    }
    if(polygon().isClosed())
    {
        painter->setBrush(brush);
        path.setFillRule(Qt::WindingFill);
        painter->drawPath(path);
    }
    painter->restore();

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

QPainterPath HIconPolylineItem::shape() const
{
    QPainterPath path;
    QRectF rectPath;
    //不是最好的方法 但现在只能用这个
    QRectF polyRect = polygon().boundingRect();
    rectPath.setX(polyRect.x() - 10);
    rectPath.setY(polyRect.y() - 10);
    rectPath.setWidth(polyRect.width() + 20);
    rectPath.setHeight(polyRect.height() + 20);
    path.addRect(rectPath);
    return path;
}

int HIconPolylineItem::type() const
{
    return enumPolyline;
}

void HIconPolylineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
   // HPropertyDlg dlg(pRectObj);
   // dlg.exec();
}

void HIconPolylineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pointStart = event->scenePos();
    pointLocation = pointInRect(pointStart);
    HIconGraphicsItem::mousePressEvent(event);
}

void HIconPolylineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal fRotateAngle = pPolylineObj->getRotateAngle();
    QTransform transform;
    transform.rotate(-fRotateAngle);
    QPointF pointEnd = transform.map(event->scenePos());
    QPointF pt = pointEnd - transform.map(pointStart);
    transform.rotate(fRotateAngle);
    pointStart = event->scenePos();

    if(pointLocation != 0)
    {
        int nRect = polygon().size();
        if(pointLocation > nRect)
            return;
        QPolygonF newPolygonF = polygon();
        if(pointLocation==1 || pointLocation==nRect)
        {
            newPolygonF.replace(0,pointEnd);
            newPolygonF.replace(nRect-1,pointEnd);
        }
        else
            newPolygonF.replace(pointLocation-1,pointEnd);
        setPolygon(newPolygonF);
    }
    else
    {
        pPolylineObj->moveBy(pt.x(),pt.y());
        HIconGraphicsItem::mouseMoveEvent(event);
    }
}


void HIconPolylineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    HIconGraphicsItem::mouseReleaseEvent(event);
}

void HIconPolylineItem::keyPressEvent(QKeyEvent *event)
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
    moveItemBy(ndx,ndy);
}

ushort HIconPolylineItem::pointInRect(QPointF& point)
{
    qreal halfpw = 14.00;
    int nRect = polygon().size();
    QRectF *pRect = new QRectF[nRect];
    for(int i = 0 ; i < nRect; i++)
    {
        pRect[i].setSize(QSizeF(halfpw,halfpw));
        pRect[i].moveCenter(polygon().at(i));
    }

    ushort location = 0;
    for(int j = 0;j < nRect;j++)
    {
        if(pRect[j].contains(point))
        {
            location = j+1;
            break;
        }
    }

    if(pRect)
    {
        delete[] pRect;
        pRect = NULL;
    }
    return location;
}

void HIconPolylineItem::setItemCursor(int location)
{
    if(location != 0)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}

void HIconPolylineItem::setPolygon(const QPolygonF & polygon)
{
    if(pyVector == polygon || polygon.size() == 0) return;
    prepareGeometryChange();
    pyVector = polygon;
    refreshBaseObj();
    update();
}

QPolygonF HIconPolylineItem::polygon() const
{
    return pyVector;
}

void HIconPolylineItem::refreshBaseObj()
{
    pPolylineObj->pylist.clear();
    foreach(QPointF pt,pyVector)
        pPolylineObj->pylist.append(mapToScene(pt));
    QPointF p = mapToScene(polygon().boundingRect().center());
    pPolylineObj->setOX(p.x());
    pPolylineObj->setOY(p.y());
    pPolylineObj->width = polygon().boundingRect().width();
    pPolylineObj->height = polygon().boundingRect().height();
    pPolylineObj->setModify(true);
}

void HIconPolylineItem::setItemObj(HBaseObj* pObj)
{
    pPolylineObj = (HPolylineObj*)pObj;
}

HBaseObj* HIconPolylineItem::getItemObj()
{
    if(pPolylineObj)
        return pPolylineObj;
    return NULL;
}

void HIconPolylineItem::moveItemBy(qreal dx,qreal dy)
{
    QPolygonF newPolygonF;// = polygon();
    foreach(QPointF pt,polygon())
    {
        pt.setX(pt.x()+dx);
        pt.setY(pt.y()+dy);
        newPolygonF<<pt;
    }
    setPolygon(newPolygonF);
}

void HIconPolylineItem::resizeItem(const QPolygonF& polygonF)
{
    if(polygonF.size() > polygon().size())
        return;
    setPolygon(polygonF);
}

