#include "hicontreewidget.h"
#include <QMenu>
#include "hiconbrower.h"
#include <QInputDialog>
#include <QMessageBox>
#include "hiconmgr.h"
HIconTreeWidgetItem::HIconTreeWidgetItem(HIconTreeWidget* parent,int type):QTreeWidgetItem(parent,type)
{


}

HIconTreeWidgetItem::HIconTreeWidgetItem(HIconTreeWidgetItem* parent,int type):QTreeWidgetItem(parent,type)
{


}

void HIconTreeWidgetItem::setUuid(QString uuid)
{
    strUuid = uuid;
}

QString HIconTreeWidgetItem::getUuid()
{
    return strUuid;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
HIconTreeWidget::HIconTreeWidget(HIconMgr* iconmgr,QWidget* parent,int type):pIconMgr(iconmgr),
    QTreeWidget(parent)
{
}

HIconTreeWidget::~HIconTreeWidget()
{

}

void HIconTreeWidget::init()
{
    HIconTreeWidgetItem *rootItem = new HIconTreeWidgetItem(this);
    rootItem->setText(0,QStringLiteral("测点"));
    addTopLevelItem(rootItem);

    digitalItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_DIGITAL);
    digitalItem->setIcon(0,QIcon(":/images/tree.png"));
    digitalItem->setText(0,QStringLiteral("遥信"));
    rootItem->addChild(digitalItem);

    analogueItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_ANALGOUE);
    analogueItem->setIcon(0,QIcon(":/images/tree.png"));
    analogueItem->setText(0,QStringLiteral("遥测"));
    rootItem->addChild(analogueItem);

    controlItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_YK);
    controlItem->setIcon(0,QIcon(":/images/tree.png"));
    controlItem->setText(0,QStringLiteral("遥控"));
    rootItem->addChild(controlItem);

    pulseItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_PLUSE);
    pulseItem->setIcon(0,QIcon(":/images/tree.png"));
    pulseItem->setText(0,QStringLiteral("遥脉"));
    rootItem->addChild(pulseItem);

    tapItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_TAP);
    tapItem->setIcon(0,QIcon(":/images/tree.png"));
    tapItem->setText(0,QStringLiteral("档位"));
    rootItem->addChild(tapItem);

    lightItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_LIGHT);
    lightItem->setIcon(0,QIcon(":/images/tree.png"));
    lightItem->setText(0,QStringLiteral("光字牌"));
    rootItem->addChild(lightItem);

    paiItem = new HIconTreeWidgetItem(this,TEMPLATE_TYPE_JDPAI);
    paiItem->setIcon(0,QIcon(":/images/tree.png"));
    paiItem->setText(0,QStringLiteral("接地牌"));
    rootItem->addChild(paiItem);

    expandAll();

}

void HIconTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint point = event->pos();
    HIconTreeWidgetItem* curItem = (HIconTreeWidgetItem*)itemAt(point);
    if(!curItem)
        return;
    int n = curItem->type();
    if(curItem->type() > TEMPLATE_TYPE_NULL && curItem->type() < TEMPLATE_TYPE_MAX)
    {
        initTemplateMenu(event);
    }
    else if(curItem->type() == TEMPLATE_TYPE_CHILD)
    {
        initTemplateChildMenu(event);
    }
}

void HIconTreeWidget::initTemplateMenu(QContextMenuEvent *event)
{
    QMenu* menu = new QMenu;
    newAct = new QAction(QStringLiteral("新建图元"),this);
    newAct->setStatusTip(QStringLiteral("新建一个图元"));
    menu->addAction(newAct);
    connect(newAct,SIGNAL(triggered(bool)),SLOT(newIcon()));
    menu->addSeparator();
    importAct = new QAction(QStringLiteral("导入图元"),this);
    importAct->setStatusTip(QStringLiteral("导入一个图元"));
    menu->addAction(importAct);

    menu->popup(event->globalPos());
}

void HIconTreeWidget::initTemplateChildMenu(QContextMenuEvent *event)
{
    QMenu* menu = new QMenu;
    renameAct = new QAction(QStringLiteral("重命名图元"),this);
    renameAct->setStatusTip(QStringLiteral("重命名一个图元"));
    menu->addAction(renameAct);
    connect(renameAct,SIGNAL(triggered(bool)),this,SLOT(renameIcon()));

    menu->addSeparator();
    delAct = new QAction(QStringLiteral("删除图元"),this);
    delAct->setStatusTip(QStringLiteral("删除一个图元"));
    menu->addAction(delAct);
    connect(delAct,SIGNAL(triggered(bool)),SLOT(deleteIcon()));



    menu->popup(event->globalPos());
}


void HIconTreeWidget::newIcon()
{
    bool ok;
    QString strName = QInputDialog::getText(this,QStringLiteral("输入图元的名称"),QStringLiteral("图元名称:"),QLineEdit::Normal,"",&ok);
    int nIconType;
    HIconTreeWidgetItem* item = (HIconTreeWidgetItem*)currentItem();
    if(item)
    {
        nIconType = item->type();
    }
    emit IconNew(strName,nIconType);
}

void HIconTreeWidget::deleteIcon()
{
    if(!pIconMgr)
        return;
    if(QMessageBox::Ok == QMessageBox::warning(NULL,QStringLiteral("删除图元"),QStringLiteral("确认删除此图元信息?"),QMessageBox::Ok|QMessageBox::Cancel))
    {
        int nIconType;
        HIconTreeWidgetItem* item = (HIconTreeWidgetItem*)currentItem();
        if(!item)
        {
            QMessageBox::warning(NULL,QStringLiteral("删除图元"),QStringLiteral("删除错误"),QMessageBox::Ok);
            return;
        }
        HIconTreeWidgetItem* itemparent = (HIconTreeWidgetItem*)item->parent();
        if(!itemparent)
            return;
        nIconType = itemparent->type();
        QString strName = itemparent->text(0);
        QString strUuid = item->data(0,Qt::UserRole).toString();//item->getUuid()
        emit IconDel(strName,nIconType,strUuid);
    }
}

void HIconTreeWidget::renameIcon()
{

}

void HIconTreeWidget::importIcon()
{

}


void HIconTreeWidget::addIconTreeWigetItem()
{
    if(!pIconMgr)
        return;
    HIconTreeWidgetItem *parentItem = (HIconTreeWidgetItem*)currentItem();
    ushort type = parentItem->type();
    if(!parentItem || (type <= TEMPLATE_TYPE_NULL || type >= TEMPLATE_TYPE_MAX))
        return;

    QString strUuid =  pIconMgr->getIconTemplate()->getUuid().toString();
    HIconTreeWidgetItem* newItem = new HIconTreeWidgetItem(parentItem,TEMPLATE_TYPE_CHILD);
    newItem->setUuid(strUuid);
    newItem->setData(0,Qt::UserRole,QVariant(strUuid));
    newItem->setText(0,pIconMgr->getIconTemplate()->getAttrName());
    parentItem->addChild(newItem);
    setCurrentItem(newItem);

}

void HIconTreeWidget::delIconTreeWidgetItem()
{
    if(!pIconMgr)
        return;
    HIconTreeWidgetItem *curItem = (HIconTreeWidgetItem*)currentItem();
    if(!curItem || curItem->type() != TEMPLATE_TYPE_CHILD) return;
    HIconTreeWidgetItem* parentItem = (HIconTreeWidgetItem*)curItem->parent();
    ushort type = parentItem->type();
    if(!curItem || (type <= TEMPLATE_TYPE_NULL || type >= TEMPLATE_TYPE_MAX))
        return;
    parentItem->removeChild(curItem);
    setCurrentItem(parentItem);
}



