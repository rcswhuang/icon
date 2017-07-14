#include "hiconscene.h"
#include "hiconframe.h"
#include "hicongraphicsitem.h"
#include "hiconlineitem.h"
#include "hiconrectitem.h"
#include "hiconellipseitem.h"
#include "hiconpolygonitem.h"
#include "hiconarcitem.h"
#include "hiconpieitem.h"
#include "hiconstate.h"
#include "hicontextitem.h"
#include "hpropertydlg.h"
#include "hiconshowpattern.h"

#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
HIconScene::HIconScene(HIconMgr* iconMgr)
    :pIconMgr(iconMgr)
{
    //pGraphicsView =
    line = 0;
    rectangle = 0;
    ellipse = 0;
    polygon = 0;
    arc = 0;
    pie = 0;
    text = 0;
}

void HIconScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF rectLogic = pIconMgr->getIconFrame()->getLogicRect();
    QRectF finalRect = rect.intersected(rectLogic);
    painter->save();
    QColor bgclr = QColor(pIconMgr->getBackgroundColor());
    painter->fillRect(finalRect,bgclr);
    painter->restore();

    bool bShowGrid = pIconMgr->getShowGrid();
    if(bShowGrid)
    {
        //int grid = pIcon
        for(qreal x=finalRect.left();x < finalRect.right()+25;x+=25)
            for(qreal y=finalRect.top();y<finalRect.bottom()+25;y+=25)
                painter->drawPoint(x,y);
    }
}


void HIconScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;
    DRAWSHAPE drawShape = pIconMgr->getIconState()->getDrawShape();
    switch (drawShape) {
    case enumLine:
    {
        line = new HIconLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
        HLineObj *pObj = new HLineObj;
        line->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(line);

    }
        break;
    case enumRectangle:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        rectangle = new HIconRectItem(tempF);
        HRectObj *pObj = new HRectObj;
        rectangle->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(rectangle);
    }
        break;
    case enumEllipse:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        ellipse = new HIconEllipseItem(tempF);
        HEllipseObj* pObj = new HEllipseObj;
        ellipse->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(ellipse);
    }
        break;
    case enumPolygon:
    {

    }
        break;
    case enumArc:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        arc = new HIconArcItem(tempF);
        pIconMgr->getIconState()->appendObj(arc->pArcObj);
        addItem(arc);
    }
        break;
    case enumPie:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        pie = new HIconPieItem(tempF);
        HPieObj* pObj = new HPieObj;
        pie->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(pie);
    }
        break;
    case enumText:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        text = new HIconTextItem(tempF);
        HTextObj* pObj = new HTextObj;
        text->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
        addItem(text);
    }
        break;
    default:
        break;
    }


    QGraphicsScene::mousePressEvent(mouseEvent);
}

void HIconScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    DRAWSHAPE drawShape = pIconMgr->getIconState()->getDrawShape();
    if(drawShape == enumLine && line != 0)
    {
        QLineF newline = QLineF(line->line().p1(),mouseEvent->scenePos());
        line->setLine(newline);

    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        QRectF newRect = QRectF(rectangle->rect().topLeft(),mouseEvent->scenePos());
        if(mouseEvent->modifiers() == Qt::ShiftModifier)
        {
            qreal dx = qAbs(mouseEvent->scenePos().x() - rectangle->rect().x());
            qreal dy = qAbs(mouseEvent->scenePos().y() - rectangle->rect().y());
            newRect = QRectF(rectangle->rect().topLeft(),QSize(qMin(dx,dy),qMin(dx,dy)));
        }
        rectangle->setRect(newRect);
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        QRectF newRect = QRectF(ellipse->rect().topLeft(),mouseEvent->scenePos());
        if(mouseEvent->modifiers() == Qt::ShiftModifier)
        {
            qreal dx = qAbs(mouseEvent->scenePos().x() - ellipse->rect().x());
            qreal dy = qAbs(mouseEvent->scenePos().y() - ellipse->rect().y());
            newRect = QRectF(ellipse->rect().topLeft(),QSize(qMin(dx,dy),qMin(dx,dy)));
        }
        ellipse->setRect(newRect);
    }
    else if(drawShape == enumPolygon && polygon != 0)
    {
        polygon->pointMove = mouseEvent->scenePos();
    }
    else if(drawShape == enumArc && arc != 0)
    {
        QRectF newRect = QRectF(arc->rect().topLeft(),mouseEvent->scenePos());
        arc->setRect(newRect);
    }
    else if(drawShape == enumPie && pie != 0)
    {
        QRectF newRect = QRectF(pie->rect().topLeft(),mouseEvent->scenePos());
        pie->setRect(newRect);
    }
    else if(drawShape == enumText && text != 0)
    {
        QRectF newRect = QRectF(text->rect().topLeft(),mouseEvent->scenePos());
        text->setRect(newRect);
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
        emit itemInserted(line->type());
        line->pLineObj->pfHeadPoint = line->line().p1();
        line->pLineObj->pfTailPoint = line->line().p2();
        line = 0;

    }
    else if(drawShape == enumRectangle && rectangle != 0)
    {
        emit itemInserted(rectangle->type());
        rectangle = 0;        
    }
    else if(drawShape == enumEllipse && ellipse != 0)
    {
        emit itemInserted(ellipse->type());
        ellipse = 0;
    }
    else if(drawShape == enumPolygon && polygon !=0)
    {
        polygon = 0;
    }
    else if(drawShape == enumArc && arc !=0)
    {
        emit itemInserted(arc->type());
        arc = 0;
    }
    else if(drawShape == enumPie && pie !=0)
    {
        emit itemInserted(pie->type());
        pie = 0;
    }
    else if(drawShape == enumText && text != 0)
    {
        emit itemInserted(text->type());
        text = 0;

    }
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

void HIconScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size() > 0)
    {
        QMenu menu;
        menu.addAction(QStringLiteral("剪切"),this,SLOT(cutItem()));
        menu.addAction(QStringLiteral("复制"),this,SLOT(copyItem()));
        menu.addAction(QStringLiteral("删除"),this,SLOT(delItem()));
        menu.addAction(QStringLiteral("属性"),this,SLOT(showProperty()));

        menu.exec(event->screenPos());
    }
}

void HIconScene::setItemProperty(QGraphicsItem* item)
{
    if(!item) return;
    HPropertyDlg dlg;
    if(item->type() == enumLine)
    {
        HIconLineItem *pItem = qgraphicsitem_cast<HIconLineItem*>(item);
        dlg.setIconObj(pItem->getItemObj());
    }
    else
    {
        //HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        //dlg.setIconObj(pItem->getItemObj());
    }

    dlg.exec();
}

void HIconScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        QGraphicsItem* item = itemList.first();
        if(item->type() == enumLine)
        {
            HIconLineItem *pItem = qgraphicsitem_cast<HIconLineItem*>(item);
            QPointF pointF = mouseEvent->scenePos();
            int location = pItem->pointInRect(pointF);
            pItem->setItemCursor(location);
        }
        else
        {
            HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
            QPointF pointF = mouseEvent->scenePos();
            int location = pItem->pointInRect(pointF);
            pItem->setItemCursor(location);
        }
    }
}

void HIconScene::setItemVisible(int nPatternId)
{
    bool bVisible = false;
    foreach (QGraphicsItem *item, items())
    {
        bVisible = false;
        if(item->type() == enumLine)
        {
            HLineObj* pObj = ((HIconLineItem*)item)->pLineObj;
            if(pObj->contains(nPatternId))
            {
                bVisible = true;
            }
        }
        else
        {
            HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
            if(pItem->getItemObj()->contains(nPatternId))
                bVisible = true;
        }
        item->setVisible(bVisible);
     }
}

//增加图元的显示方案
void HIconScene::addItemByPatternId(int nPatternId)
{
    if(!pIconMgr && !pIconMgr->getIconTemplate() &&!pIconMgr->getIconTemplate()->getSymbol())
        return;
    HIconSymbol *pSymbol = pIconMgr->getIconTemplate()->getSymbol();
    HIconShowPattern* pattern = pSymbol->findPatternById(nPatternId);
    if(!pattern) return;
    for(int i = 0; i < pattern->pObjList.count();i++)
    {
        HBaseObj* pObj = (HBaseObj*)pattern->pObjList.at(i);
        if(!pObj) continue;
        if(pObj->getShapeType() == enumLine)
        {
            //line = new HIconLineItem()
        }
    }
}

//删除图元的显示方案
void HIconScene::delItemByPatternId(int nPatternId)
{
    foreach (QGraphicsItem *item, items())
    {
        if(item->type() == enumLine)
        {
            HBaseObj* pObj = qgraphicsitem_cast<HIconLineItem*>(item)->getItemObj();
            if(pObj->contains(nPatternId))
            {
                removeItem(item);
                delete item;
            }
        }
        else
        {
            HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
            HBaseObj *pObj = pItem->getItemObj();
            if(pObj->contains(nPatternId))
            {
                removeItem(item);
                delete item;
            }
        }
     }
}

void HIconScene::cutItem()
{

}

void HIconScene::copyItem()
{

}

//右键删除已经选择的图元元素
void HIconScene::delItem()
{
    if(!pIconMgr && !pIconMgr->getIconTemplate())
        return;
    HIconSymbol* pSymbol = pIconMgr->getIconTemplate()->getSymbol();
    if(!pSymbol)
        return;
    foreach (QGraphicsItem *item, selectedItems()) {
        if(item->type() == enumLine)
            pSymbol->delObj(qgraphicsitem_cast<HIconLineItem*>(item)->pLineObj);
        else
        {
            HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
            pSymbol->delObj(pItem->getItemObj());
        }
        removeItem(item);
        delete item;
     }

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


