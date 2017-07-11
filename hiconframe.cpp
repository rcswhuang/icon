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
    QRectF rect = QRectF(-500,-500,1000,1000);
    setLogicRect(rect);
}

HIconFrame::HIconFrame(HIconMgr* pMgr,QWidget * parent, Qt::WindowFlags f)
:pIconMgr(pMgr),HFrame(parent,f)
{
    m_pView->setScene(new HIconScene(pIconMgr));
    QRectF logicRectF = pIconMgr->getLogicRect();
    setLogicRect(logicRectF);
}

HIconFrame::~HIconFrame()
{

}

void HIconFrame::setIconMgr(HIconMgr *iconmgr)
{
    pIconMgr = iconmgr;

    QRectF logicRectF = pIconMgr->getLogicRect();
    setLogicRect(logicRectF);
}

void HIconFrame::setLogicRect(QRectF &rectF)
{
    sceneRect = rectF;
    if(m_pView)
        m_pView->setSceneRect(rectF);

}

//绘制路径
void HIconFrame::drawPath(const QList<Path>& pathList)
{
    QPainter painter(this);
    QPen pen = pathList[0].pen;
    pen.setWidth(1);
    painter.setPen(pen);
    QPainterPath path = pathList[0].painterPath;
    painter.drawPath(path);
}

//结束绘制
void HIconFrame::endDraw()
{

}


//对象的创建
void HIconFrame::objCreated(HBaseObj* obj)
{
    if(!m_pView || !m_pView->scene())
        return;

  //  pIconScene->addLine(0,0,100,100,QPen(QColor(Qt::red)));
}
/*
//对象的删除
void HIconFrame::objRemoved(HDrawObj* obj)
{

}
*/
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

//选中对象发生改变
//void HIconFrame::onSelectChanged(HDrawObj* obj,bool bSelect);

//重新计算选中点、选中框
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

void HIconFrame::delItemByPatternId(int nPatternId)
{
    if(iconScene())
    {
        iconScene()->delItemByPatternId(nPatternId);
    }
}
