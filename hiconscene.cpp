#include "hiconscene.h"
#include "hiconframe.h"
#include <QGraphicsSceneMouseEvent>
#include "hiconlineitem.h"
#include "hiconrectitem.h"
#include "hiconellipseitem.h"
#include "hiconpolygonitem.h"
#include "hiconarcitem.h"
#include "hiconpieitem.h"
#include "hiconstate.h"
#include "hicontextitem.h"
#include "hpropertydlg.h"
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
        pIconMgr->getIconState()->appendObj(line->pLineObj);
        addItem(line);

    }
        break;
    case enumRectangle:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        rectangle = new HIconRectItem(tempF);
        pIconMgr->getIconState()->appendObj(rectangle->pRectObj);
        addItem(rectangle);
    }
        break;
    case enumEllipse:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        ellipse = new HIconEllipseItem(tempF);
        pIconMgr->getIconState()->appendObj(ellipse->pEllipseObj);
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
        pIconMgr->getIconState()->appendObj(pie->pPieObj);
        addItem(pie);
    }
        break;
    case enumText:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        text = new HIconTextItem(tempF);
        pIconMgr->getIconState()->appendObj(text->pTextObj);
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
        ellipse->pEllipseObj->topLeft = ellipse->rect().topLeft();
        ellipse->pEllipseObj->rectWidth = ellipse->rect().width();
        ellipse->pEllipseObj->rectHeight = ellipse->rect().height();

        emit itemInserted(ellipse->type());
        ellipse = 0;
    }
    else if(drawShape == enumPolygon && polygon !=0)
    {
        //pt = mouseEvent->scenePos();
        polygon->pyVector<<mouseEvent->scenePos();
        polygon->pointStart = mouseEvent->scenePos();
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
        HIconLineItem *cItem = static_cast<HIconLineItem*>(item);
        dlg.setIconObj(cItem->pLineObj);
    }
    else if(item->type() == enumEllipse)
    {
        HIconEllipseItem *cItem = static_cast<HIconEllipseItem*>(item);
        dlg.setIconObj(cItem->pEllipseObj);
    }
    else if(item->type() == enumRectangle)
    {
        HIconRectItem *cItem = static_cast<HIconRectItem*>(item);
        dlg.setIconObj(cItem->pRectObj);
    }
    else if(item->type() == enumArc)
    {
        HIconArcItem *cItem = static_cast<HIconArcItem*>(item);
        dlg.setIconObj(cItem->pArcObj);
    }
    else if(item->type() == enumPie)
    {
        HIconPieItem *cItem = static_cast<HIconPieItem*>(item);
        dlg.setIconObj(cItem->pPieObj);
    }
    else if(item->type() == enumText)
    {
        HIconTextItem *cItem = static_cast<HIconTextItem*>(item);
        dlg.setIconObj(cItem->pTextObj);
    }

    dlg.exec();

}

void HIconScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        QGraphicsItem* pItem = itemList.first();
        if(pItem->type() == enumLine)
        {
            HIconLineItem *eItem = static_cast<HIconLineItem*>(pItem);
            QPointF pointF = mouseEvent->scenePos();
            int location = eItem->pointInRect(pointF);
            eItem->setItemCursor(location);
        }
        else if(pItem->type() == enumEllipse)
        {
            HIconEllipseItem *eItem = static_cast<HIconEllipseItem*>(pItem);
            QPointF pointF = mouseEvent->scenePos();
            int location = eItem->pointInRect(pointF);
            eItem->setItemCursor(location);
        }
        else if(pItem->type() == enumRectangle)
        {
            HIconRectItem *eItem = static_cast<HIconRectItem*>(pItem);
            QPointF pointF = mouseEvent->scenePos();
            int location = eItem->pointInRect(pointF);
            eItem->setItemCursor(location);
        }
        else if(pItem->type() == enumArc)
        {
            HIconArcItem *eItem = static_cast<HIconArcItem*>(pItem);
            QPointF pointF = mouseEvent->scenePos();
            int location = eItem->pointInRect(pointF);
            eItem->setItemCursor(location);
        }
        else if(pItem->type() == enumPie)
        {
            HIconPieItem *eItem = static_cast<HIconPieItem*>(pItem);
            QPointF pointF = mouseEvent->scenePos();
            int location = eItem->pointInRect(pointF);
            eItem->setItemCursor(location);
        }
        else if(pItem->type() == enumText)
        {
            HIconTextItem *eItem = static_cast<HIconTextItem*>(pItem);
            QPointF pointF = mouseEvent->scenePos();
            int location = eItem->pointInRect(pointF);
            eItem->setItemCursor(location);
        }

    }
}

void HIconScene::setItemVisible(int nPatternId)
{
    QList<QGraphicsItem *> pItemList = items();
    bool bVisible = false;
    for(int i = 0; i < pItemList.count();i++)
    {
        QGraphicsItem* pItem = (QGraphicsItem*)pItemList[i];
        int drawShape = pItem->type();
        if(pItem)
        {
            bVisible = false;
            if(drawShape == enumLine)
            {
                HLineObj* pObj = ((HIconLineItem*)pItem)->pLineObj;
                if(pObj->contains(nPatternId))
                {
                    bVisible = true;
                }
            }
            else if(drawShape == enumRectangle)
            {
                HRectObj* pObj = ((HIconRectItem*)pItem)->pRectObj;
                if(pObj->contains(nPatternId))
                {
                    bVisible = true;
                }
            }
            else if(drawShape == enumEllipse)
            {
                HEllipseObj* pObj = ((HIconEllipseItem*)pItem)->pEllipseObj;
                if(pObj->contains(nPatternId))
                {
                    bVisible = true;
                }
            }
            else if(drawShape == enumArc)
            {
                HArcObj* pObj = ((HIconArcItem*)pItem)->pArcObj;
                if(pObj->contains(nPatternId))
                {
                    bVisible = true;
                }
            }
            else if(drawShape == enumPie)
            {
                HPieObj* pObj = ((HIconPieItem*)pItem)->pPieObj;
                if(pObj->contains(nPatternId))
                {
                    bVisible = true;
                }
            }
            else if(drawShape == enumText)
            {
                HTextObj* pObj = ((HIconTextItem*)pItem)->pTextObj;
                if(pObj->contains(nPatternId))
                {
                    bVisible = true;
                }
            }
            pItem->setVisible(bVisible);
        }
    }
}

void HIconScene::delItemByPatternId(int nPatternId)
{
    QList<QGraphicsItem *> itemList = items();
    //bool bDel = false;
    while(itemList.count())
    {
        QGraphicsItem* pItem = (QGraphicsItem*)itemList.takeFirst();
        int drawShape = pItem->type();
        if(!pItem) continue;

        if(drawShape == enumLine)
        {
            HLineObj* pObj = ((HIconLineItem*)pItem)->pLineObj;
            if(pObj->contains(nPatternId))
            {
                removeItem(pItem);
            }
        }
        else if(drawShape == enumRectangle)
        {
            HRectObj* pObj = ((HIconRectItem*)pItem)->pRectObj;
            if(pObj->contains(nPatternId))
            {
                removeItem(pItem);
            }
        }
        else if(drawShape == enumEllipse)
        {
            HEllipseObj* pObj = ((HIconEllipseItem*)pItem)->pEllipseObj;
            if(pObj->contains(nPatternId))
            {
                removeItem(pItem);
            }
        }
        else if(drawShape == enumArc)
        {
            HArcObj* pObj = ((HIconArcItem*)pItem)->pArcObj;
            if(pObj->contains(nPatternId))
            {
                removeItem(pItem);
            }
        }
        else if(drawShape == enumPie)
        {
            HPieObj* pObj = ((HIconPieItem*)pItem)->pPieObj;
            if(pObj->contains(nPatternId))
            {
                removeItem(pItem);
            }
        }
        else if(drawShape == enumText)
        {
            HTextObj* pObj = ((HIconTextItem*)pItem)->pTextObj;
            if(pObj->contains(nPatternId))
            {
                removeItem(pItem);
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

void HIconScene::delItem()
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size() > 0)
    {
        while(itemList.count())
        {
            QGraphicsItem* pItem = itemList.takeFirst();
            int drawShape = pItem->type();
            if(pItem)
            {
                if(drawShape == enumLine)
                    pIconMgr->getIconTemplate()->getSymbol()->delObj(((HIconLineItem*) pItem)->pLineObj);
                else if(drawShape == enumRectangle)
                    pIconMgr->getIconTemplate()->getSymbol()->delObj(((HIconRectItem*) pItem)->pRectObj);
                else if(drawShape == enumEllipse)
                    pIconMgr->getIconTemplate()->getSymbol()->delObj(((HIconEllipseItem*) pItem)->pEllipseObj);
                else if(drawShape == enumArc)
                    pIconMgr->getIconTemplate()->getSymbol()->delObj(((HIconArcItem*) pItem)->pArcObj);
                else if(drawShape == enumPie)
                    pIconMgr->getIconTemplate()->getSymbol()->delObj(((HIconPieItem*) pItem)->pPieObj);
                else if(drawShape == enumText)
                    pIconMgr->getIconTemplate()->getSymbol()->delObj(((HIconTextItem*) pItem)->pTextObj);
                removeItem(pItem);
            }
        }
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


