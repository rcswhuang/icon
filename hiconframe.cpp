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
    //寻找当前页面的所有选择的图元
    QByteArray bytes;
    QDataStream stream(bytes,QIODevice::WriteOnly);
    QList<QGraphicsItem*> itemSelectList = iconScene()->selectedItems();
    stream<<itemSelectList.count();
    stream<<pIconMgr->getIconTemplate()->getSymbol()->getCurrentPattern();
    for(int i =0; i < itemSelectList.count();i++)
    {
        HBaseObj* pObj = qgraphicsitem_cast<HIconGraphicsItem*>(itemSelectList[i])->getItemObj();
        HBaseObj* pNewObj = pObj->clone();
        pNewObj->writeData(&stream);
    }
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream cbStream(file);
        cbStream<<0x0000;
        cbStream.writeBytes(bytes.data(),bytes.length());
        file.close();
    }
}

void HIconFrame::copy()
{

}

void HIconFrame::paste()
{
    QString clipboardPath = getClipboardFile();
    QFile file(clipboardPath);
    if(!file.exists() || file.open(QIODevice::ReadOnly))
        return;
    QDataStream stream(&file);
    quint32 magicNumber;
    stream>>magicNumber;
    int num;
    stream>>num;
    int nPattern;
    stream>>nPattern;
    for(int i = 0; i < num;i++)
    {

    }

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

bool HIconFrame::eventFilter( QObject *obj, QEvent *event)
{
    HFrame::eventFilter(obj,event);



    return false;
}

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
    QString clipboardPath = QProcessEnvironment::systemEnvironment().value("WFSYSTEM_DIR");
    clipboardPath.append("/data/icon");
    QDir dirClipboard(clipboardPath);
    if(!dirClipboard.exists())
        dirClipboard.mkdir(clipboardPath);
    clipboardPath.append("/iconclipboard.data");
    return clipboardPath;
}
