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
#include "hiconselectionitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
HIconScene::HIconScene(HIconMgr* iconMgr)
    :pIconMgr(iconMgr)
{
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
    if(getItemAt(mouseEvent->scenePos()))
        pIconMgr->getIconState()->setDrawShape(enumMulSelection);

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
        HArcObj* pObj = new HArcObj;
        arc->setItemObj(pObj);
        pIconMgr->getIconState()->appendObj(pObj);
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
    case enumMulSelection:
    {
        QRectF tempF;
        tempF.setTopLeft(mouseEvent->scenePos());
        tempF.setBottomRight(mouseEvent->scenePos());
        select = new HIconSelectionItem(tempF);
        addItem(select);
    }
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
    else if(drawShape == enumMulSelection)
    {
        QRectF newRect = QRectF(select->rect().topLeft(),mouseEvent->scenePos());
        select->setRect(newRect);
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
    else if(drawShape == enumMulSelection && select != 0)
    {
        //计算选择点
        removeItem(select);
        delete select;
        select = 0
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

bool HIconScene::getItemAt(const QPointF &pos)
{
    QTransform transform;
    QGraphicsItem* item = itemAt(pos,transform);
    if(item)
        return true;
    return false;
}

void HIconScene::setItemProperty(QGraphicsItem* item)
{
    if(!item) return;
    HPropertyDlg dlg;
    HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
    dlg.setIconObj(pItem->getItemObj());
    dlg.exec();
}

void HIconScene::setItemCursor(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> itemList = selectedItems();
    if(itemList.size()== 1)
    {
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(itemList.first());
        QPointF pointF = mouseEvent->scenePos();
        int location = pItem->pointInRect(pointF);
        pItem->setItemCursor(location);
    }
}

void HIconScene::setItemVisible(int nPatternId)
{
    bool bVisible = false;
    foreach (QGraphicsItem *item, items())
    {
        bVisible = false;
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(pItem->getItemObj()->contains(nPatternId))
            bVisible = true;
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
    int drawShape = enumNo;
    foreach(HBaseObj* pObj,pattern->pObjList)
    {
        if(!pObj) continue;
        drawShape = pObj->getShapeType();
        if(drawShape == enumLine)
        {
            line = new HIconLineItem(QLineF(((HLineObj*) pObj)->pfHeadPoint,((HLineObj*)pObj)->pfTailPoint));
            line->setItemObj(pObj);
            addItem(line);
        }
        else if(drawShape == enumRectangle)
        {
            HRectObj* pObj1 = (HRectObj*)pObj;
            rectangle = new HIconRectItem(QRectF(QPointF(pObj1->topLeft),QSizeF(pObj1->rectWidth,pObj1->rectHeight)));
            rectangle->setItemObj(pObj);
            addItem(rectangle);
        }
        else if(drawShape == enumEllipse)
        {
            HEllipseObj* pObj1 = (HEllipseObj*)pObj;
            ellipse = new HIconEllipseItem(QRectF(QPointF(pObj1->topLeft),QSizeF(pObj1->rectWidth,pObj1->rectHeight)));
            ellipse->setItemObj(pObj);
            addItem(ellipse);
        }
        else if(drawShape == enumArc)
        {
            HArcObj* pObj1 = (HArcObj*)pObj;
            arc = new HIconArcItem(QRectF(QPointF(pObj1->topLeft),QSizeF(pObj1->rectWidth,pObj1->rectHeight)));
            arc->setItemObj(pObj);
            addItem(arc);
        }
        else if(drawShape == enumPie)
        {
            HPieObj* pObj1 = (HPieObj*)pObj;
            pie = new HIconPieItem(QRectF(QPointF(pObj1->topLeft),QSizeF(pObj1->rectWidth,pObj1->rectHeight)));
            pie->setItemObj(pObj);
            addItem(pie);
        }
        else if(drawShape == enumText)
        {
            HTextObj* pObj1 = (HTextObj*)pObj;
            text = new HIconTextItem(QRectF(QPointF(pObj1->getTopLeftPoint()),QSizeF(pObj1->getRectWidth(),pObj1->getRectHeight())));
            text->setItemObj(pObj);
            addItem(text);
        }

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

}

//删除图元的显示方案
void HIconScene::delItemByPatternId(int nPatternId)
{
    foreach (QGraphicsItem *item, items())
    {
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        if(!pItem) continue;
        HBaseObj *pObj = pItem->getItemObj();
        if(pObj->contains(nPatternId))
        {
            removeItem(item);
            delete item;
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
    foreach (QGraphicsItem *item, selectedItems())
    {
        HIconGraphicsItem* pItem = qgraphicsitem_cast<HIconGraphicsItem*>(item);
        pSymbol->delObj(pItem->getItemObj());
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


