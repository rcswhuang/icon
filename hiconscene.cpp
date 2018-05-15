#include "hiconscene.h"
#include "hiconframe.h"
#include "hicongraphicsitem.h"
#include "hiconlineitem.h"
#include "hiconrectitem.h"
#include "hiconellipseitem.h"
#include "hiconcircleitem.h"
#include "hiconpolygonitem.h"
#include "hiconpolylineitem.h"
#include "hiconarcitem.h"
#include "hiconpieitem.h"
#include "hiconstate.h"
#include "hicontextitem.h"
#include "hiconitemgroup.h"
#include "hiconcomplexitem.h"
#include "hiconshowpattern.h"
#include "hiconselectionitem.h"
#include "hiconcommand.h"
#include "hiconproperty.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
HIconScene::HIconScene(HIconMgr* iconMgr)
    :pIconMgr(iconMgr)
{
    line = 0;
    rectangle = 0;
    ellipse = 0;
    circle = 0;
    polygon = 0;
    polyline = 0;
    arc = 0;
    pie = 0;
    text = 0;
}

void HIconScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(!pIconMgr && !pIconMgr->getIconFrame())
        return;
    QRectF rectLogic = pIconMgr->getIconFrame()->getLogicRect();
    QRectF finalRect = rectLogic;//rect.intersected(rectLogic);
    painter->save();
    QColor bgclr = QColor(pIconMgr->getBackgroundColor());
    painter->fillRect(finalRect,bgclr);


    bool bShowGrid = pIconMgr->getShowGrid();
    if(bShowGrid)
    {
        for(qreal x=finalRect.left();x < finalRect.right()+25;x+=25)
            for(qreal y=finalRect.top();y<finalRect.bottom()+25;y+=25)
                painter->drawPoint(x,y);
    }

    bool bShowCenterLine = pIconMgr->getShowCenterLine();
    if(bShowCenterLine)
    {
        QPointF p1(rectLogic.left()+5,(rectLogic.topLeft().y()+rectLogic.bottomLeft().y())/2);
        QPointF p2(rectLogic.right()-5,(rectLogic.topLeft().y()+rectLogic.bottomLeft().y())/2);
        QPointF p3((rectLogic.topLeft().x()+rectLogic.topRight().x())/2,rectLogic.top()+5);
        QPointF p4((rectLogic.topLeft().x()+rectLogic.topRight().x())/2,rectLogic.bottom()-5);
        QPen pen(Qt::lightGray);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawLine(p1,p2);
        painter->drawLine(p3,p4);
    }
    painter->restore();
}


void HIconScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;

    bLeftShift = true;
    prePoint = mouseEvent->scenePos();
    DRAWSHAPE drawShape = pIconMgr->getIconState()->getDrawShape();
    //处于选择状态同时没有选到任何item,就是多选状态
    if(drawShape == enumSelection)
    {
        //如果选择到东西 先把选择到的取消掉 就可以了
        QPointF pt = mouseEvent->scenePos();
        if(!getItemAt(pt))
        {
            drawShape = enumMulSelection;
            pIconMgr->getIconState()->setDrawShape(enumMulSelection);
            nSelectMode = enumNo;
        }
        else
        {
            nSelectMode = enumSelect;
        }
        if(nSelectMode == enumSelect)
        {
            if(pointInRect(pt) != 0)
                nSelectMode = enumSize;
            else
                nSelectMode = enumMove;
        }
    }
    switch (drawShape) {
    case enumLine:
    {
        line = new HIconLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumLine);
        line->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(line);
        addNewIconCommand(pObj);
    }
        break;
    case enumRectangle:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        rectangle = new HIconRectItem(tempF);
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumRectangle);
        rectangle->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(rectangle);
        addNewIconCommand(pObj);
    }
        break;
    case enumEllipse:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        ellipse = new HIconEllipseItem(tempF);
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumEllipse);
        ellipse->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(ellipse);
        addNewIconCommand(pObj);
    }
        break;
    case enumCircle:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        circle = new HIconCircleItem(tempF);
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumCircle);
        circle->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(circle);
        addNewIconCommand(pObj);
    }
        break;
    case enumPolygon:
    {
        if(polygon == 0)
        {
            QPolygonF tempF;
            tempF<<prePoint<<prePoint;
            polygon = new HIconPolygonItem(tempF);
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumPolygon);
            polygon->setItemObj(pObj);
            pIconMgr->getIconState()->appendObj(pObj);
            addItem(polygon);
            addNewIconCommand(polygon->getItemObj());
        }
        else
        {
            QPolygonF tempF = polygon->polygon();
            tempF.replace(tempF.length()-1,prePoint);
            tempF.append(prePoint);
            polygon->setPolygon(tempF);
            //addNewIconCommand(polygon->getItemObj());
        }
    }
        break;
    case enumPolyline:
    {
        if(polyline == 0)
        {
            QPolygonF tempF;
            tempF<<prePoint<<prePoint;
            polyline = new HIconPolylineItem(tempF);
            HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumPolyline);
            polyline->setItemObj(pObj);
            pIconMgr->getIconState()->appendObj(pObj);
            addItem(polyline);
            addNewIconCommand(polyline->getItemObj());
        }
        else
        {
            QPolygonF tempF = polyline->polygon();
            tempF.replace(tempF.length()-1,prePoint);
            tempF.append(prePoint);
            polyline->setPolygon(tempF);
            //addNewIconCommand(polygon->getItemObj());
        }
    }
        break;
    case enumArc:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        arc = new HIconArcItem(tempF);
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumArc);
        arc->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(arc);
        addNewIconCommand(pObj);
    }
        break;
    case enumPie:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        pie = new HIconPieItem(tempF);
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumPie);
        pie->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(pie);
        addNewIconCommand(pObj);
    }
        break;
    case enumText:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        text = new HIconTextItem(tempF);
        HBaseObj *pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumText);
        text->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(text);
        addNewIconCommand(pObj);
    }
        break;
    case enumMulSelection:
    {
        QRectF tempF = QRectF(prePoint,prePoint).normalized();
        select = new HIconSelectionItem(tempF);
        addItem(select);
        break;
    }
    default:
        break;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void HIconScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    DRAWSHAPE drawShape = pIconMgr->getIconState()->getDrawShape();
    curPoint = mouseEvent->scenePos();
    if(drawShape == enumLine && line != 0)
    {
        QLineF newline = QLineF(prePoint,curPoint);
        line->setLine(newline);
    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        rectangle->setRect(newRect);
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        ellipse->setRect(newRect);
    }
    else if(drawShape == enumCircle && circle != 0)
    {
        qreal dx = qAbs(curPoint.x() - prePoint.x());
        qreal dy = qAbs(curPoint.y() - prePoint.x());
        QRectF newRect = QRectF(prePoint,QSize(qMin(dx,dy),qMin(dx,dy)));
        circle->setRect(newRect);
    }
    else if(drawShape == enumPolygon && polygon != 0)
    {
        QPolygonF tempF = polygon->polygon();
        tempF.replace(tempF.length()-1,curPoint);
        polygon->setPolygon(tempF);
    }
    else if(drawShape == enumPolyline && polyline != 0)
    {
        QPolygonF tempF = polyline->polygon();
        tempF.replace(tempF.length()-1,curPoint);
        polyline->setPolygon(tempF);
    }
    else if(drawShape == enumArc && arc != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        arc->setRect(newRect);
    }
    else if(drawShape == enumPie && pie != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        pie->setRect(newRect);
    }
    else if(drawShape == enumText && text != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        text->setRect(newRect);
    }
    else if(drawShape == enumMulSelection && select != 0)
    {
        QRectF newRect = QRectF(prePoint,curPoint).normalized();
        select->setRect(newRect.normalized());
    }
    //判断当前是否处于选择状态
    if(drawShape == enumSelection)
    {
        setItemCursor(mouseEvent);
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void HIconScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{   
    DRAWSHAPE drawShape = pIconMgr->getIconState()->getDrawShape();
    if(drawShape == enumLine && line != 0)
    {
        line->getItemObj()->setModify(true);
        emit itemInserted(line->type());
        line = 0;
    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        rectangle->getItemObj()->setModify(true);
        emit itemInserted(rectangle->type());
        rectangle = 0;        
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        ellipse->getItemObj()->setModify(true);
        emit itemInserted(ellipse->type());
        ellipse = 0;
    }
    else if(drawShape == enumCircle && circle != 0)
    {
        circle->getItemObj()->setModify(true);
        emit itemInserted(circle->type());
        circle = 0;
    }
    else if(drawShape == enumArc && arc !=0)
    {
        arc->getItemObj()->setModify(true);
        emit itemInserted(arc->type());
        arc = 0;
    }
    else if(drawShape == enumPie && pie !=0)
    {
        pie->getItemObj()->setModify(true);
        emit itemInserted(pie->type());
        pie = 0;
    }
    else if(drawShape == enumText && text != 0)
    {
        text->getItemObj()->setModify(true);
        emit itemInserted(text->type());
        text = 0;
    }
    else if(drawShape == enumPolygon && polygon != 0)
    {
        return QGraphicsScene::mouseReleaseEvent(mouseEvent);;
    }
    else if(drawShape == enumPolyline && polyline !=0)
    {
        return QGraphicsScene::mouseReleaseEvent(mouseEvent);;
    }
    else if(drawShape == enumMulSelection && select != 0)
    {
        //计算选择点
        QRectF rectF = select->rect();
        calcSelectedItem(rectF);//判断item是否选到 选到就是enumSelect否则enumNo
        removeItem(select);
        delete select;
        select = 0;
    }


    //要检查是不是移动过
    if(nSelectMode == enumMove && bLeftShift)
    {
        prepareMoveItem(mouseEvent);
    }
    if(nSelectMode == enumSize && bLeftShift)
    {
        prepareRezieItem(mouseEvent);
    }
    bLeftShift = false;
    pIconMgr->getIconState()->setDrawShape(enumSelection);
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void HIconScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        QGraphicsItem* pItem = itemList.first();
        setItemProperty(pItem);
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void HIconScene::keyPressEvent(QKeyEvent *event)
{
    //解决多个item同时移动的问题
    QList<QGraphicsItem*> itemList = selectedItems();
    foreach(QGraphicsItem* item,itemList)
    {
        sendEvent(item,event);
    }
}

void HIconScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    DRAWSHAPE drawShape = pIconMgr->getIconState()->getDrawShape();
    if(drawShape == enumPolygon && polygon != 0)
    {
        if(polygon->polygon().size()<=2)
        {
            HBaseObj* pObj = polygon->getItemObj();
            pObj->setDeleted(true);
            polygon->setVisible(false);
        }
        else
        {
            QPolygonF tempF = polygon->polygon();
            tempF.replace(tempF.size()-1,event->scenePos());
            tempF.append(tempF.at(0));
            polygon->setPolygon(tempF);
        }
        polygon->getItemObj()->setModify(true);
        emit itemInserted(polygon->type());
        polygon = 0;
        //pIconMgr->getIconState()->setDrawShape(enumSelection);
        return;
    }
    else if(drawShape == enumPolyline && polyline != 0)
    {

        if(polyline->polygon().size()<=2)
        {
            HBaseObj* pObj = polyline->getItemObj();
            pObj->setDeleted(true);
            polyline->setVisible(false);
        }
        else
        {
            QPolygonF tempF = polyline->polygon();
            tempF.replace(tempF.size()-1,event->scenePos());
            //tempF.append(tempF.at(0));
            polyline->setPolygon(tempF);
        }
        polyline->getItemObj()->setModify(true);
        emit itemInserted(polyline->type());
        polyline = 0;

        //pIconMgr->getIconState()->setDrawShape(enumSelection);
        return;
    }

    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size() > 0)
    {
        QMenu menu;
        menu.addAction(QStringLiteral("剪切"),this,SLOT(cutItem()));
        menu.addAction(QStringLiteral("复制"),this,SLOT(copyItem()));
        menu.addAction(QStringLiteral("删除"),this,SLOT(delItem()));
        menu.addAction(QStringLiteral("粘贴"),this,SLOT(pasteItem()));
        menu.addAction(QStringLiteral("属性"),this,SLOT(showProperty()));
        menu.exec(event->screenPos());
    }
    else
    {
        if(!pIconMgr || !pIconMgr->getIconFrame())
            return;

        QFile strFile(pIconMgr->getIconFrame()->getClipboardFile());
        if(strFile.exists())
        {
            QMenu menu;
            menu.addAction(QStringLiteral("粘贴"),this,SLOT(pasteItem()));
            menu.exec(event->screenPos());
        }
    }
}

bool HIconScene::getItemAt(const QPointF &pos)
{
    //判断当前点位置是否有item被选择
    QTransform transform;
    QGraphicsItem* item = itemAt(pos,transform);
    if(item)
    {
        return true;
    }
    return false;
}

//如果任一选择对象处于resize状态就返回对应位置,注意每次只能改变一个对象的size
int HIconScene::pointInRect(QPointF& pointF)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    foreach(QGraphicsItem*item,itemList)
    {
        int location = ((HIconGraphicsItem*)item)->pointInRect(pointF);
        if(location != 0)
        {
            oldPolygonF.clear();
            getIconGraphicsItemPointList((HIconGraphicsItem*)item,oldPolygonF);
            return location;
        }
    }
    //nSelectMode = enumSelect;
    return 0;
}

void HIconScene::setItemProperty(QGraphicsItem* item)
{
    if(!item) return;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    HBaseObj* pObj = pItem->getItemObj();
    HPropertyDlg dlg(pObj);
    dlg.exec();

}

void HIconScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    //获取所在item，只要item选择到即可
    //这个地方要改，只要获取当前选择那个，如果是多个选择则返回
    QPointF pointF = mouseEvent->scenePos();
   /* QTransform transform;

    QGraphicsItem* item = itemAt(pointF,transform);
    if(itemList.indexOf(item) == -1)
        return;*/
    if(itemList.count()>=2 || itemList.count() == 0) return;
    QGraphicsItem* item = itemList.at(0);
    if(!item) return;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    int location = pItem->pointInRect(pointF);
    pItem->setItemCursor(location);
}

void HIconScene::setItemVisible(int nPatternId)
{
    bool bVisible = false;
    foreach (QGraphicsItem *item, items())
    {
        bVisible = false;
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(pItem->getItemObj()->contains(nPatternId) && false == pItem->getItemObj()->isDeleted() )
            bVisible = true;
        item->setVisible(bVisible);
     }
}

//增加图元的显示方案 ---能不能把这些拉出来独立成一个函数 huangw
void HIconScene::addItemByPatternId(int nPatternId)
{
    if(!pIconMgr && !pIconMgr->getIconTemplate() &&!pIconMgr->getIconTemplate()->getSymbol())
        return;
    HIconSymbol *pSymbol = pIconMgr->getIconTemplate()->getSymbol();
    HIconShowPattern* pattern = pSymbol->findPatternById(nPatternId);
    if(!pattern) return;
    int drawShape = enumNo;
    foreach(HBaseObj* pObj,pattern->pObjList)
    {
        if(!pObj) continue;
        drawShape = pObj->getShapeType();
        int nZValue = pObj->getStackOrder();
        if(drawShape == enumLine)
        {
            line = new HIconLineItem(QLineF(((HLine*) pObj)->getHeadPoint(),((HLine*)pObj)->getTailPoint()));
            line->setItemObj(pObj);
            line->setZValue(nZValue);
            addItem(line);

        }
        else if(drawShape == enumRectangle)
        {
            HRectangle* pObj1 = (HRectangle*)pObj;
            rectangle = new HIconRectItem(pObj1->getObjRect());
            rectangle->setItemObj(pObj);
            rectangle->setZValue(nZValue);
            addItem(rectangle);
        }
        else if(drawShape == enumEllipse)
        {
            HEllipse* pObj1 = (HEllipse*)pObj;
            ellipse = new HIconEllipseItem(pObj1->getObjRect());
            ellipse->setItemObj(pObj);
            ellipse->setZValue(nZValue);
            addItem(ellipse);
        }
        else if(drawShape == enumCircle)
        {
            HCircle* pObj1 = (HCircle*)pObj;
            circle = new HIconCircleItem(pObj1->getObjRect());
            circle->setItemObj(pObj);
            circle->setZValue(nZValue);
            addItem(circle);
        }
        else if(drawShape == enumPolygon)
        {
            HPolygon* pObj1 = (HPolygon*)pObj;
            polygon = new HIconPolygonItem(pObj1->pylist);
            polygon->setItemObj(pObj);
            polygon->setZValue(nZValue);
            addItem(polygon);
        }
        else if(drawShape == enumPolyline)
        {
            HPolyline* pObj1 = (HPolyline*)pObj;
            polyline = new HIconPolylineItem(pObj1->pylist);
            polyline->setItemObj(pObj);
            polyline->setZValue(nZValue);
            addItem(polyline);
        }
        else if(drawShape == enumArc)
        {
            HArc* pObj1 = (HArc*)pObj;
            arc = new HIconArcItem(pObj1->getObjRect());
            arc->setItemObj(pObj);
            arc->setZValue(nZValue);
            addItem(arc);
        }
        else if(drawShape == enumPie)
        {
            HPie* pObj1 = (HPie*)pObj;
            pie = new HIconPieItem(pObj1->getObjRect());
            pie->setItemObj(pObj);
            pie->setZValue(nZValue);
            addItem(pie);
        }
        else if(drawShape == enumText)
        {
            HText* pObj1 = (HText*)pObj;
            text = new HIconTextItem(pObj1->getObjRect());
            text->setItemObj(pObj);
            text->setZValue(nZValue);
            addItem(text);
        }
        else if(drawShape == enumGroup)
        {
            HGroupObj* pObj1 = (HGroupObj*)pObj;
            group = new HIconItemGroup(pObj1->getObjRect());
            group->setItemObj(pObj);
            group->setZValue(nZValue);
            addItem(group);
        }

        if(drawShape == enumLine && line != 0)
        {
            line = 0;
        }
        else if(drawShape == enumRectangle && rectangle != 0)
        {
            rectangle = 0;
        }
        else if(drawShape == enumEllipse && ellipse != 0)
        {
            ellipse = 0;
        }
        else if(drawShape == enumCircle && circle != 0)
        {
            circle = 0;
        }
        else if(drawShape == enumPolyline && polyline != 0)
        {
            polyline = 0;
        }
        else if(drawShape == enumPolygon && polygon !=0)
        {
            polygon = 0;
        }
        else if(drawShape == enumArc && arc !=0)
        {
            arc = 0;
        }
        else if(drawShape == enumPie && pie !=0)
        {
            pie = 0;
        }
        else if(drawShape == enumText && text != 0)
        {
            text = 0;
        }
        else if(drawShape == enumGroup && group != 0)
        {
            group = 0;
        }
    }
}

//删除图元的显示方案
void HIconScene::delItemByPatternId(int nPatternId)
{
    if(!pIconMgr || !pIconMgr->getIconTemplate() || !pIconMgr->getIconTemplate()->getSymbol())
        return;
    foreach (QGraphicsItem *item, items())
    {
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(!pItem) continue;
        HBaseObj *pObj = pItem->getItemObj();
        //必须先从pIconSymbol里面删除掉
        if(pObj->contains(nPatternId))
        {
            pIconMgr->getIconTemplate()->getSymbol()->takeObj(pObj);
            removeItem(item);
            delete item;
        }
     }
}

void HIconScene::cutItem()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
    pIconMgr->getIconFrame()->cut();
}

void HIconScene::copyItem()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
     pIconMgr->getIconFrame()->copy();
}

void HIconScene::pasteItem()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
    pIconMgr->getIconFrame()->paste();
}

//右键删除已经选择的图元元素
void HIconScene::delItem()
{
    if(!pIconMgr || !pIconMgr->getIconFrame())
        return;
    if(QMessageBox::Cancel == QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确认删除该图符吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        return;
    pIconMgr->getIconFrame()->del();
}

void HIconScene::showProperty()
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        QGraphicsItem* pItem = itemList.first();
        setItemProperty(pItem);
    }
}

void HIconScene::calcSelectedItem(const QRectF &rectF)
{
    QPainterPath path;
    path.addRect(rectF);
    QTransform transform;
    setSelectionArea(path,transform);
}

//复制粘贴拷贝里面用到的函数
HIconGraphicsItem* HIconScene::addItemByIconObj(int nPattern,HBaseObj* pObj)
{
    if(!pObj) return NULL;
    pObj->nPattern = (quint8)nPattern;
    quint8 drawShape = pObj->getShapeType();
    HIconGraphicsItem* item = NULL;
    if(drawShape == enumLine)
    {
        HLine* pObj1 = (HLine*)pObj;
        line = new HIconLineItem(QLineF(((HLine*) pObj)->getHeadPoint(),((HLine*)pObj)->getTailPoint()));
        line->setItemObj(pObj1);
        addItem(line);
    }
    else if(drawShape == enumRectangle)
    {
        HRectangle* pObj1 = (HRectangle*)pObj;
        rectangle = new HIconRectItem(pObj1->getObjRect());
        rectangle->setItemObj(pObj1);
        addItem(rectangle);
    }
    else if(drawShape == enumEllipse)
    {
        HEllipse* pObj1 = (HEllipse*)pObj;
        ellipse = new HIconEllipseItem(pObj1->getObjRect());
        ellipse->setItemObj(pObj1);
        addItem(ellipse);
    }
    else if(drawShape == enumCircle)
    {
        HCircle* pObj1 = (HCircle*)pObj;
        circle = new HIconCircleItem(pObj1->getObjRect());
        circle->setItemObj(pObj1);
        addItem(circle);
    }
    else if(drawShape == enumPolygon)
    {
        HPolygon* pObj1 = (HPolygon*)pObj;
        polygon = new HIconPolygonItem(pObj1->pylist);
        polygon->setItemObj(pObj1);
        addItem(polygon);
    }
    else if(drawShape == enumPolyline)
    {
        HPolyline* pObj1 = (HPolyline*)pObj;
        polyline = new HIconPolylineItem(pObj1->pylist);
        polyline->setItemObj(pObj1);
        addItem(polyline);
    }
    else if(drawShape == enumArc)
    {
        HArc* pObj1 = (HArc*)pObj;
        arc = new HIconArcItem(pObj1->getObjRect());
        arc->setItemObj(pObj1);
        addItem(arc);
    }
    else if(drawShape == enumPie)
    {
        HPie* pObj1 = (HPie*)pObj;
        pie = new HIconPieItem(pObj1->getObjRect());
        pie->setItemObj(pObj1);
        addItem(pie);
    }
    else if(drawShape == enumText)
    {
        HText* pObj1 = (HText*)pObj;
        text = new HIconTextItem(QRectF(QPointF(pObj1->getTopLeftPoint()),QSizeF(pObj1->getRectWidth(),pObj1->getRectHeight())));
        text->setItemObj(pObj1);
        addItem(text);
    }


    if(drawShape == enumLine && line != 0)
    {
        item = line;
        line = 0;
    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        item = rectangle;
        rectangle = 0;
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        item = ellipse;
        ellipse = 0;
    }
    else if(drawShape == enumCircle && circle != 0)
    {
        item = circle;
        circle = 0;
    }
    else if(drawShape == enumPolyline && polyline !=0 )
    {
        item = polyline;
        polyline = 0;
    }
    else if(drawShape == enumPolygon && polygon !=0)
    {
        item = polygon;
        polygon = 0;
    }
    else if(drawShape == enumArc && arc !=0)
    {
        item = arc;
        arc = 0;
    }
    else if(drawShape == enumPie && pie !=0)
    {
        item = pie;
        pie = 0;
    }
    else if(drawShape == enumText && text != 0)
    {
        item = text;
        text = 0;
    }

    return item;
}

void HIconScene::addNewIconCommand(HBaseObj *pObj)
{
    if(!pIconMgr || !pIconMgr->getIconUndoStack())
        return;
    HNewIconCommand* newIconCommand = new HNewIconCommand(pIconMgr,pObj);
    pIconMgr->getIconUndoStack()->push(newIconCommand);
}

void HIconScene::prepareMoveItem(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> selectedItemList = selectedItems();
    if(selectedItemList.count() == 0) return;
    QPointF pt = mouseEvent->scenePos();
    if(fabs(pt.x()-prePoint.x()) < 0.0001 && fabs(pt.y() - prePoint.y()) < 0.0001)
        return;
    qreal dx = pt.x() - prePoint.x();
    qreal dy = pt.y() - prePoint.y();
    QList<HBaseObj*> objList;
    for(int i = 0; i < selectedItemList.count();i++)
    {
        HIconGraphicsItem* item = (HIconGraphicsItem*)selectedItemList.at(i);
        if(!item) continue;
        objList.append(item->getItemObj());
    }
    HMoveIconCommand* moveIconCommand = new HMoveIconCommand(pIconMgr,objList,dx,dy);
    pIconMgr->getIconUndoStack()->push(moveIconCommand);
}

void HIconScene::prepareRezieItem(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    //获取所在item，只要item选择到即可
    QTransform transform;
    QPointF pt = mouseEvent->scenePos();
    QGraphicsItem* item = itemAt(pt,transform);
    if(itemList.indexOf(item) == -1)
        return;
    if(fabs(pt.x()-prePoint.x()) < 0.0001 && fabs(pt.y() - prePoint.y()) < 0.0001)
        return;
    newPolygonF.clear();
    getIconGraphicsItemPointList((HIconGraphicsItem*)item,newPolygonF);
    HIconGraphicsItem* iconItem = (HIconGraphicsItem*)item;
    QList<HBaseObj*> objList;
    objList.append(iconItem->getItemObj());
    //每次只能改变一个
    HResizeIconCommand* resizeIconCommand = new HResizeIconCommand(pIconMgr,objList,oldPolygonF,newPolygonF);
    pIconMgr->getIconUndoStack()->push(resizeIconCommand);

}

void HIconScene::getIconGraphicsItemPointList(HIconGraphicsItem* item,QList<QPolygonF>& pfList)
{
    if(item == NULL) return;
    pfList.clear();
    int nDrawShape = item->type();
    QPolygonF pf;
    pf.clear();
    if(nDrawShape == enumLine)
    {
        HIconLineItem* pItem = (HIconLineItem*)item;
        QLineF lineF = pItem->line();
        pf<<lineF.p1()<<lineF.p2();
    }
    else if(nDrawShape == enumRectangle)
    {
        HIconRectItem* pItem = (HIconRectItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumEllipse)
    {
        HIconEllipseItem* pItem = (HIconEllipseItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumCircle)
    {
        HIconCircleItem* pItem = (HIconCircleItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumPolyline)
    {
        HIconPolylineItem* pItem = (HIconPolylineItem*)item;
        pf = pItem->polygon();
    }
    else if(nDrawShape == enumPolygon)
    {
        HIconPolygonItem* pItem = (HIconPolygonItem*)item;
        pf = pItem->polygon();
    }
    else if(nDrawShape == enumArc)
    {
        HIconArcItem* pItem = (HIconArcItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumPie)
    {
        HIconPieItem* pItem = (HIconPieItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    else if(nDrawShape == enumText)
    {
        HIconTextItem* pItem = (HIconTextItem*)item;
        QRectF rectF = pItem->rect();
        pf<<rectF.topLeft()<<rectF.topRight()<<rectF.bottomLeft()<<rectF.bottomRight();
    }
    pfList.append(pf);
}

void HIconScene::addIconGraphicsItem(HBaseObj* pObj)
{
    DRAWSHAPE drawShape = pObj->getShapeType();
    int nZValue = pObj->getStackOrder();
    if(drawShape == enumLine)
    {
        line = new HIconLineItem(QLineF(((HLine*) pObj)->getHeadPoint(),((HLine*)pObj)->getTailPoint()));
        line->setItemObj(pObj);
        line->setZValue(nZValue);
        addItem(line);

    }
    else if(drawShape == enumRectangle)
    {
        HRectangle* pObj1 = (HRectangle*)pObj;
        rectangle = new HIconRectItem(pObj1->getObjRect());
        rectangle->setItemObj(pObj);
        rectangle->setZValue(nZValue);
        addItem(rectangle);
    }
    else if(drawShape == enumEllipse)
    {
        HEllipse* pObj1 = (HEllipse*)pObj;
        ellipse = new HIconEllipseItem(pObj1->getObjRect());
        ellipse->setItemObj(pObj);
        ellipse->setZValue(nZValue);
        addItem(ellipse);
    }
    else if(drawShape == enumCircle)
    {
        HCircle* pObj1 = (HCircle*)pObj;
        circle = new HIconCircleItem(pObj1->getObjRect());
        circle->setItemObj(pObj);
        circle->setZValue(nZValue);
        addItem(circle);
    }
    else if(drawShape == enumPolygon)
    {
        HPolygon* pObj1 = (HPolygon*)pObj;
        polygon = new HIconPolygonItem(pObj1->pylist);
        polygon->setItemObj(pObj);
        polygon->setZValue(nZValue);
        addItem(polygon);
    }
    else if(drawShape == enumPolyline)
    {
        HPolyline* pObj1 = (HPolyline*)pObj;
        polyline = new HIconPolylineItem(pObj1->pylist);
        polyline->setItemObj(pObj);
        polyline->setZValue(nZValue);
        addItem(polyline);
    }
    else if(drawShape == enumArc)
    {
        HArc* pObj1 = (HArc*)pObj;
        arc = new HIconArcItem(pObj1->getObjRect());
        arc->setItemObj(pObj);
        arc->setZValue(nZValue);
        addItem(arc);
    }
    else if(drawShape == enumPie)
    {
        HPie* pObj1 = (HPie*)pObj;
        pie = new HIconPieItem(pObj1->getObjRect());
        pie->setItemObj(pObj);
        pie->setZValue(nZValue);
        addItem(pie);
    }
    else if(drawShape == enumText)
    {
        HText* pObj1 = (HText*)pObj;
        text = new HIconTextItem(pObj1->getObjRect());
        text->setItemObj(pObj);
        text->setZValue(nZValue);
        addItem(text);
    }

    //还有复杂图形的解决 ----huangw

}

void HIconScene::groupObj()
{
    QList<QGraphicsItem*> items = selectedItems();
    if(items.count() < 2) return;

    HBaseObj* pGroupObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(enumGroup);
    QRectF groupRect;
    for(int i = 0; i < items.count();i++)
    {
        HIconGraphicsItem* item = (HIconGraphicsItem*)items.at(i);
        HBaseObj* pObj = item->getItemObj();
        groupRect = groupRect.united(item->rect());
        pIconMgr->getIconTemplate()->getSymbol()->takeObj(pObj);//应该是take操作 不是删除
        ((HGroupObj*)pGroupObj)->addObj(pObj);
    }
    //矩形
    HIconItemGroup *itemGroup = new HIconItemGroup(QRectF(0,0,groupRect.width(),groupRect.height()));
    pIconMgr->getIconState()->appendObj(pGroupObj);
    itemGroup->setItemObj(pGroupObj);
    itemGroup->setRect(groupRect);
    foreach(QGraphicsItem* item,items)
    {
        removeItem(item);
        HBaseObj* pObj = ((HIconGraphicsItem*)item)->getItemObj();
        pObj->setIconGraphicsItem(NULL);
    }
    addItem(itemGroup);
    pIconMgr->getIconState()->setDrawShape(enumSelection);
}

void HIconScene::ungroupObj()
{
    QList<QGraphicsItem*> items = pIconMgr->getIconFrame()->iconScene()->selectedItems();
    for(int i = 0; i < items.count();i++)
    {
        HIconGraphicsItem* item = (HIconGraphicsItem*)items.at(i);
        if(item->type() != enumGroup) continue;
        //removeItem(item);
        HBaseObj* pObj = item->getItemObj();
        HGroupObj* pGroupObj = (HGroupObj*)pObj;
        while(!pGroupObj->isEmpty())
        {
            HBaseObj* pObj = (HBaseObj*)pGroupObj->takeFirst();
            pIconMgr->getIconState()->appendObj(pObj);
            addIconGraphicsItem(pObj);
        }
        removeItem(item);
        pIconMgr->getIconTemplate()->getSymbol()->delObj(pObj);
    }
    pIconMgr->getIconState()->setDrawShape(enumSelection);
}
