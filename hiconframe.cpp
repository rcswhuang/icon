#include "hiconframe.h"
#include <QVBoxLayout>
#include "hevent.h"
#include "hiconscene.h"
#include "hiconobjitem.h"
#include "hiconmgr.h"
#include "hiconstate.h"
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

//刷新选中点、选中框
void HIconFrame::refreshSelected(const QRectF& rect)
{

}

//鼠标的改变
void HIconFrame::cursorChanged(const QCursor& cursor)
{

}

//合适宽度
void HIconFrame::fitWidth()
{

}

//合适高度
void HIconFrame::fitHeight()
{

}


//按照显示方案来显示里面的Item
void HIconFrame::setItemVisible(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->setItemVisible(nPatternId);
    }
}

//事件过滤
bool HIconFrame::eventFilter( QObject *obj, QEvent *event)
{
    HFrame::eventFilter(obj,event);



    return false;
}

//增加某个图元的显示方案
void HIconFrame::addItemByPatternId(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->addItemByPatternId(nPatternId);
    }
}

//删除某个图元的显示方案
void HIconFrame::delItemByPatternId(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->delItemByPatternId(nPatternId);
    }
}
