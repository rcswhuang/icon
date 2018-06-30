#include "hiconframe.h"
#include <QVBoxLayout>
#include <QByteArray>
#include <QDataStream>
#include <QProcessEnvironment>
#include "hiconscene.h"
#include "hiconmgr.h"
#include "hiconstate.h"
#include "hicongraphicsitem.h"
#include "hiconcommand.h"

HIconFrame::HIconFrame(QWidget * parent, Qt::WindowFlags f )
    :HFrame(parent,f)
{
    pIconMgr = NULL;
    m_pView->setInteractive(false);
    m_pView->setDragMode(QGraphicsView::NoDrag);
}

HIconFrame::HIconFrame(HIconMgr* pMgr,QWidget * parent, Qt::WindowFlags f)
:pIconMgr(pMgr),HFrame(parent,f)
{
    m_pView->setScene(new HIconScene(pIconMgr));
}

HIconFrame::~HIconFrame()
{

}

void HIconFrame::setIconMgr(HIconMgr *iconmgr)
{
    pIconMgr = iconmgr;
}

void HIconFrame::setLogicRect(QRectF &rectF)
{
    if(rectF == sceneRect)
        return;
    sceneRect = rectF;
    if(m_pView)
    {
        m_pView->setSceneRect(rectF);
        int f_width = width();
        int f_height = height();
        resize(f_width-1,f_height);
        resize(f_width,f_height);
    }
}

QRectF HIconFrame::getLogicRect()
{
    return sceneRect;
}

HIconScene* HIconFrame::iconScene()
{
    if(m_pView)
        return (HIconScene*)m_pView->scene();
    return NULL;
}

void HIconFrame::refreshSelected(const QRectF& rect)
{

}

void HIconFrame::cursorChanged(const QCursor& cursor)
{

}

void HIconFrame::setItemVisible(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->setItemVisible(nPatternId);
    }
}
/*
bool HIconFrame::eventFilter( QObject *obj, QEvent *event)
{
    HFrame::eventFilter(obj,event);



    return false;
}*/

HIconGraphicsItem* HIconFrame::addItemByIconObj(int nPattern,HBaseObj* pObj)
{
    if(iconScene())
    {
        return iconScene()->addItemByIconObj(nPattern,pObj);
    }
    return NULL;
}


//？？ 应该是刷新函数
void HIconFrame::addItemByPatternId(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->addItemByPatternId(nPatternId);
    }
}

void HIconFrame::delItemByPatternId(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->delItemByPatternId(nPatternId);
    }
}

HIconGraphicsItem* HIconFrame::getIconGraphicsItemByObj(HBaseObj *pObj)
{
    if(!pObj || !iconScene()) return NULL;
    QList<QGraphicsItem*> items = iconScene()->items();
    foreach (QGraphicsItem *item1, items)
    {
        HIconGraphicsItem* item = qgraphicsitem_cast<HIconGraphicsItem*>(item1);
        if(!item) continue;
        if(pObj->getShapeType() != item->type()) continue;
        HBaseObj* obj = item->getItemObj();
        if(obj->getObjID() == pObj->getObjID())
            return item;
    }
    return NULL;
}






