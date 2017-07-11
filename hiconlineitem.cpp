#include "hiconlineitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainterPathStroker>
#include <QKeyEvent>
#include <math.h>
#include "hpropertydlg.h"
#include "hiconobj.h"


HIconLineItem::HIconLineItem(QGraphicsItem *parent):QGraphicsLineItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

HIconLineItem::HIconLineItem(const QLineF &line, QGraphicsItem *parent):QGraphicsLineItem(line,parent)
{
    //setAcceptDrops(true);
    pointLocation = LOCATIONNO;
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    pLineObj = new HLineObj();
    //bSelected = false;
    setSelected(false);
}


QRectF HIconLineItem::boundingRect() const
{
    return shape().controlPointRect();
}


bool HIconLineItem::contains(const QPointF &point) const
{
    return shape().boundingRect().contains(point);
}


void HIconLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QColor penClr = QColor(pLineObj->getLineColorName());
    int penWidth = pLineObj->getLineWidth();
    Qt::PenStyle penStyle = pLineObj->getLineStyle();
    Qt::PenCapStyle capStyle = pLineObj->getLineCapStyle();

    QPen pen = QPen(penClr);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    pen.setCapStyle(capStyle);
    painter->setPen(pen);
    //

    //画箭头
    if(pLineObj->getArrowWidth() > 0 && pLineObj->getArrowHeight() > 0)
    {

        double angle = ::acos(line().dx() / line().length());
        if(line().dy() >= 0)
            angle = (PI*2) - angle;
        int w = pLineObj->getArrowWidth();
        int h = pLineObj->getArrowHeight();
        quint16 arrowLength = sqrt(w*w+h*h);
        quint8 arrowS = pLineObj->getArrowStart();
        quint8 arrowE = pLineObj->getArrowEnd();
        QPointF arrowP1;
        QPointF arrowP2;
        if(arrowS == 1)
        {
            arrowP1 = line().p1() + QPointF(sin(angle+PI/3)*arrowLength,cos(angle+PI/3)*arrowLength);
            arrowP2 = line().p1() + QPointF(sin(angle+PI - PI/3)*arrowLength,cos(angle+PI-PI/3)*arrowLength);

            painter->drawLine(line());
            painter->drawLine(arrowP1,line().p1());
            painter->drawLine(arrowP2,line().p1());
        }
        else if(arrowS == 2)
        {
            line().setLength(line().length() - w);
            painter->drawLine(line());
            arrowP1 = line().p1() + QPointF(sin(angle+PI/3)*arrowLength,cos(angle+PI/3)*arrowLength);
            arrowP2 = line().p1() + QPointF(sin(angle+PI - PI/3)*arrowLength,cos(angle+PI-PI/3)*arrowLength);
            QPolygonF arrowHead;
            arrowHead<<line().p1()<<arrowP1<<arrowP2;
            painter->drawPolygon(arrowHead);
        }
        else if(arrowS == 3)
        {
            painter->drawLine(line());
            arrowP1 = line().p1() + QPointF(sin(angle+PI/3)*arrowLength,cos(angle+PI/3)*arrowLength);
            arrowP2 = line().p1() + QPointF(sin(angle+PI - PI/3)*arrowLength,cos(angle+PI-PI/3)*arrowLength);
            QPolygonF arrowHead;
            arrowHead<<line().p1()<<arrowP1<<arrowP2;
            painter->save();
            painter->setBrush(QColor(penClr));
            painter->drawPolygon(arrowHead);
            painter->restore();
        }

        if(arrowE == 1)
        {
            arrowP1 = line().p2() + QPointF(sin(angle-PI/3)*arrowLength,cos(angle-PI/3)*arrowLength);
            arrowP2 = line().p2() + QPointF(sin(angle-PI + PI/3)*arrowLength,cos(angle-PI+PI/3)*arrowLength);

            painter->drawLine(line());
            painter->drawLine(arrowP1,line().p2());
            painter->drawLine(arrowP2,line().p2());
        }
        else if(arrowE == 2)
        {

        }
        else if(arrowE == 3)
        {
            painter->drawLine(line());
            arrowP1 = line().p2() + QPointF(sin(angle-PI/3)*arrowLength,cos(angle-PI/3)*arrowLength);
            arrowP2 = line().p2() + QPointF(sin(angle-PI + PI/3)*arrowLength,cos(angle-PI+PI/3)*arrowLength);
            QPolygonF arrowHead;
            arrowHead<<line().p1()<<arrowP1<<arrowP2;
            painter->save();
            painter->setBrush(QColor(penClr));
            painter->drawPolygon(arrowHead);
            painter->restore();
        }
    }
    else
        painter->drawLine(line());


    if(isSelected())
    {
        QPen pen1 = QPen(penClr,penWidth,penStyle);
        painter->setPen(pen1);
        QLineF line1 = line();
        painter->drawLine(line1);
        QPointF p1 = line().p1();
        QPointF p2 = line().p2();
        pen1.setStyle(Qt::SolidLine);
        painter->setPen(pen1);
        QRectF rectF1;
        rectF1.setSize(QSizeF(10,10));
        rectF1.moveCenter(p1);
        QRectF rectF2;
        rectF2.setSize(QSize(10,10));
        rectF2.moveCenter(p2);
        painter->drawRect(rectF1);
        painter->drawRect(rectF2);
    }
}


QPainterPath HIconLineItem::shape() const
{
    QPainterPath path;// = QGraphicsLineItem::shape();
    QPainterPathStroker ps;
    ps.setWidth(20);
    path.moveTo(line().p1());
    path.lineTo(line().p2());
    return ps.createStroke(path);
    //return path;
}

int HIconLineItem::type() const
{
    return enumLine;
}

void HIconLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    curPointF = event->scenePos();
    if((pointLocation = pointInRect(curPointF))!=LOCATIONNO)
        lineMode = LineSize;

    QGraphicsLineItem::mousePressEvent(event);
}

void HIconLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //setCursor(Qt::SizeAllCursor);
    //shift键
    //setSelected(false);
    QPointF sizeF = event->scenePos() - curPointF;
    QLineF line1 = line();//
    curPointF = event->scenePos();
    if(lineMode == LineSize)
    {
        if(pointLocation == LOCATIONLEFT)
        {
           line1 = QLineF(line1.p1()+sizeF,line1.p2());
        }
        else if(pointLocation == LOCATIONRIGHT)
        {
            line1 = QLineF(line1.p1(),line1.p2() + sizeF);
        }
        setLine(line1);
    }
    else
    {
        QGraphicsLineItem::mouseMoveEvent(event);
    }
}

void HIconLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    lineMode = LineNo;

    QGraphicsLineItem::mouseReleaseEvent(event);
}

void HIconLineItem::keyPressEvent(QKeyEvent *event)
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
    QPointF p1 = QPointF(line().p1().x() + ndx,line().p1().y() + ndy);
    QPointF p2 = QPointF(line().p2().x() + ndx,line().p2().y() + ndy);
    QLineF newLine = QLineF(p1,p2);
    setLine(newLine);
}

QVariant HIconLineItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange)
    {
        pLineObj->pfHeadPoint = mapToScene(line().p1());
        pLineObj->pfTailPoint = mapToScene(line().p2());
    }
    return QGraphicsItem::itemChange(change,value);
}

ushort HIconLineItem::pointInRect(QPointF &point)
{
    QPointF p1 = mapToScene(line().p1());
    QPointF p2 = mapToScene(line().p2());
    QRectF rectF1;
    rectF1.setSize(QSizeF(10,10));
    rectF1.moveCenter(p1);
    QRectF rectF2;
    rectF2.setSize(QSize(10,10));
    rectF2.moveCenter(p2);
    if(rectF1.contains(point))
        return LOCATIONLEFT;
    else if(rectF2.contains(point))
        return LOCATIONRIGHT;
    return LOCATIONNO;
}

void HIconLineItem::setItemCursor(int position)
{
    if(position == 1)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else if(position == 2)
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}
