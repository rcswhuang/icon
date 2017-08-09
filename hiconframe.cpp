#include "hiconframe.h"
#include <QVBoxLayout>
#include <QByteArray>
#include <QDataStream>
#include <QProcessEnvironment>
#include <QDir>
#include "hiconscene.h"
#include "hiconobjitem.h"
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

void HIconFrame::fitWidth()
{

}

void HIconFrame::fitHeight()
{

}

void HIconFrame::cut()
{
    copy();
    del();
}

void HIconFrame::copy()
{
    //寻找当前页面的所有选择的图元
    QByteArray bytes;
    QDataStream stream(&bytes,QIODevice::WriteOnly);
    QList<QGraphicsItem*> itemSelectList = iconScene()->selectedItems();
    stream<<itemSelectList.count();
    stream<<pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern();
    for(int i =0; i < itemSelectList.count();i++)
    {
        HBaseObj* pObj = qgraphicsitem_cast<HIconGraphicsItem*>(itemSelectList[i])->getItemObj();
        if(!pObj) continue;
        stream<<(quint8)pObj->getShapeType();
        HBaseObj* pNewObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(pObj->getShapeType());
        if(!pNewObj) continue;
        pObj->clone(pNewObj);//需要clone吗？
        pNewObj->writeData(&stream);
        if(pNewObj)
        {
            delete pNewObj;
            pNewObj = NULL;
        }
    }
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream cbStream(&file);
       // cbStream<<0x0000;
        cbStream.writeRawData(bytes.data(),bytes.length());
        file.close();
    }
}

void HIconFrame::paste()
{
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
        return;
    QList<HIconGraphicsItem*> copyItemList;
    QDataStream stream(&file);
    int num;
    stream>>num;
    int nPattern;
    stream>>nPattern;
    quint8 nType;
    QList<HBaseObj*> objList;
    for(int i = 0; i < num;i++)
    {
        stream>>nType;
        HBaseObj* pObj = pIconMgr->getIconTemplate()->getSymbol()->newObj(nType);
        if(!pObj) continue;
        pObj->readData(&stream);
        objList.append(pObj);
        HIconGraphicsItem* item = addItemByIconObj(pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern(),pObj);
        if(!item)
        {
            delete pObj;
            pObj = NULL;
            iconScene()->removeItem(item);
            delete item;
            item = NULL;
            continue;
        }
        copyItemList.append(item);
        pIconMgr->getIconTemplate()->getSymbol()->addObj(pObj);
     }

    //改变选择状态，只选择拷贝后的图元元素
    foreach(QGraphicsItem* item,iconScene()->items())
    {
        item->setSelected(false);
    }
    foreach(HIconGraphicsItem* item,copyItemList)
    {
        item->setSelected(true);
    }

    //
    if(nPattern == pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern())
    {
        for(int i = 0; i < copyItemList.count();i++)
        {
            HIconGraphicsItem* pItem = (HIconGraphicsItem*)copyItemList[i];
            if(!pItem) continue;
            QPointF pt(10,10);
            pItem->moveBy(pt.x(),pt.y());
            pItem->getItemObj()->moveBy(pt.x(),pt.y());
        }
    }
    iconScene()->update(getLogicRect());
    HPasteIconCommand* pasteIconCommand = new HPasteIconCommand(pIconMgr,objList);
    pIconMgr->getIconUndoStack()->push(pasteIconCommand);
}

void HIconFrame::del()
{
    QList<QGraphicsItem*> itemSelectList = iconScene()->selectedItems();
    QList<HBaseObj*> objList;
    foreach(QGraphicsItem* item,itemSelectList)
    {
        if(!item) continue;
        //不能直接删除 改成deleted=TRUE，只有到保存的时候才真正删除对象
        HBaseObj* pObj = ((HIconGraphicsItem*)item)->getItemObj();
        pObj->setDeleted(true);
        item->setVisible(false);
        objList.append(pObj);
    }
    HDelIconCommand *delIconCommand = new HDelIconCommand(pIconMgr,objList);
    pIconMgr->getIconUndoStack()->push(delIconCommand);
}

void HIconFrame::bringToTop()
{
    if(iconScene())
        iconScene()->bringToTop();
}

void HIconFrame::bringToBottom()
{
    if(iconScene())
        iconScene()->bringToBottom();
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

QString HIconFrame::getClipboardFile()
{
    QString clipboardPath = QProcessEnvironment::systemEnvironment().value("wfsystem_dir");
    clipboardPath.append("/data/icon");
    QDir dirClipboard(clipboardPath);
    if(!dirClipboard.exists())
        dirClipboard.mkdir(clipboardPath);
    clipboardPath.append("/iconclipboard.data");
    return clipboardPath;
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






