﻿#include "hicontreewidget.h"
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
    setSortingEnabled(false);
}

HIconTreeWidget::~HIconTreeWidget()
{

}

void HIconTreeWidget::init()
{
    setHeaderLabel(QStringLiteral("图元浏览"));
    HIconTreeWidgetItem *normalItem = new HIconTreeWidgetItem(this);
    normalItem->setText(0,QStringLiteral("普通类"));
    addTopLevelItem(normalItem);
    HIconTreeWidgetItem *measureItem = new HIconTreeWidgetItem(this);
    measureItem->setText(0,QStringLiteral("测点类"));
    addTopLevelItem(measureItem);
    HIconTreeWidgetItem *otherAllItem = new HIconTreeWidgetItem(this);
    otherAllItem->setText(0,QStringLiteral("其他类"));
    addTopLevelItem(otherAllItem);
    expandItem(normalItem);
    expandItem(measureItem);
    expandItem(otherAllItem);

    //普通类
    trans2Item = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_TRANSFORMER2);
    trans2Item->setIcon(0,QIcon(":/images/tree.png"));
    trans2Item->setText(0,QStringLiteral("两卷变"));

    trans3Item = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_TRANSFORMER3);
    trans3Item->setIcon(0,QIcon(":/images/tree.png"));
    trans3Item->setText(0,QStringLiteral("三卷变"));

    generatorItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_GENERATOR);
    generatorItem->setIcon(0,QIcon(":/images/tree.png"));
    generatorItem->setText(0,QStringLiteral("发电机"));

    capacitorItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_CAPACITOR);
    capacitorItem->setIcon(0,QIcon(":/images/tree.png"));
    capacitorItem->setText(0,QStringLiteral("电容器"));

    otherdeviceItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_OTHERDEVICE);
    otherdeviceItem->setIcon(0,QIcon(":/images/tree.png"));
    otherdeviceItem->setText(0,QStringLiteral("其他设备"));

    ptItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_PT);
    ptItem->setIcon(0,QIcon(":/images/tree.png"));
    ptItem->setText(0,QStringLiteral("电压互感器"));

    ctItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_CT);
    ctItem->setIcon(0,QIcon(":/images/tree.png"));
    ctItem->setText(0,QStringLiteral("电流互感器"));

    arresterItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_ARRESTER);
    arresterItem->setIcon(0,QIcon(":/images/tree.png"));
    arresterItem->setText(0,QStringLiteral("避雷器"));

    reactorItem = new HIconTreeWidgetItem(normalItem,TEMPLATE_TYPE_REACTOR);
    reactorItem->setIcon(0,QIcon(":/images/tree.png"));
    reactorItem->setText(0,QStringLiteral("容抗器"));

    //测点类
    digitalItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_DIGITAL);
    digitalItem->setIcon(0,QIcon(":/images/tree.png"));
    digitalItem->setText(0,QStringLiteral("遥信"));

    analogueItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_ANALOGUE);
    analogueItem->setIcon(0,QIcon(":/images/tree.png"));
    analogueItem->setText(0,QStringLiteral("遥测"));

    relayItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_RELAY);
    relayItem->setIcon(0,QIcon(":/images/tree.png"));
    relayItem->setText(0,QStringLiteral("遥控"));

    pulseItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_PLUSE);
    pulseItem->setIcon(0,QIcon(":/images/tree.png"));
    pulseItem->setText(0,QStringLiteral("遥脉"));

    tapItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_TAP);
    tapItem->setIcon(0,QIcon(":/images/tree.png"));
    tapItem->setText(0,QStringLiteral("档位"));
    //rootItem->addChild(tapItem);

    lightItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_LIGHT);
    lightItem->setIcon(0,QIcon(":/images/tree.png"));
    lightItem->setText(0,QStringLiteral("光字牌"));

    controlItem = new HIconTreeWidgetItem(measureItem,TEMPLATE_TYPE_CONTROL);
    controlItem->setIcon(0,QIcon(":/images/tree.png"));
    controlItem->setText(0,QStringLiteral("控制点"));

    //其他类
    paiItem = new HIconTreeWidgetItem(otherAllItem,TEMPLATE_TYPE_JDPAI);
    paiItem->setIcon(0,QIcon(":/images/tree.png"));
    paiItem->setText(0,QStringLiteral("接地牌"));

    otherItem = new HIconTreeWidgetItem(otherAllItem,TEMPLATE_TYPE_OTHER);
    otherItem->setIcon(0,QIcon(":/images/tree.png"));
    otherItem->setText(0,QStringLiteral("其他"));

    //connect(this,SIGNAL(itemSelectionChanged()),SLOT(openIcon()));
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(openIcon(QTreeWidgetItem*,int)));
    initTemplateFile();
    //expandAll();

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
    QString strTemplateName = QInputDialog::getText(this,QStringLiteral("输入图元的名称"),QStringLiteral("图元名称:"),QLineEdit::Normal,"",&ok);
    if(!ok) return;
    HIconTreeWidgetItem* item = (HIconTreeWidgetItem*)currentItem();
    if(!item) return;
    emit IconNew(strTemplateName,item->text(0),item->type());
}

void HIconTreeWidget::openIcon(QTreeWidgetItem* item,int col)
{
    HIconTreeWidgetItem* pCurItem = dynamic_cast<HIconTreeWidgetItem*> (item);
    if(!pCurItem) return;
    int nTemplateType = pCurItem->type();
    if(nTemplateType > TEMPLATE_TYPE_NULL && nTemplateType < TEMPLATE_TYPE_MAX)
    {
        expandIconItem(pCurItem);
    }
    else if(nTemplateType == TEMPLATE_TYPE_CHILD)
    {
        QString strTemplateName = pCurItem->text(col);
        QString strTemplateUuid = pCurItem->getUuid();
        if(!pCurItem->parent())
            return;
        nTemplateType = pCurItem->parent()->type();
        if(strTemplateName.isEmpty() || strTemplateUuid.isEmpty())
            return;
        emit IconOpen(strTemplateName,nTemplateType,strTemplateUuid);
    }
}

void HIconTreeWidget::deleteIcon()
{
    if(!pIconMgr)
        return;
    if(QMessageBox::Ok == QMessageBox::warning(NULL,QStringLiteral("删除图元"),QStringLiteral("确认删除此图元信息?"),QMessageBox::Ok|QMessageBox::Cancel))
    {
        int nCatalogType;
        HIconTreeWidgetItem* item = (HIconTreeWidgetItem*)currentItem();
        if(!item)
        {
            QMessageBox::warning(NULL,QStringLiteral("删除图元"),QStringLiteral("删除错误"),QMessageBox::Ok);
            return;
        }
        HIconTreeWidgetItem* itemparent = (HIconTreeWidgetItem*)item->parent();
        if(!itemparent)
            return;
        nCatalogType = itemparent->type();
        QString stCatalogrName = itemparent->text(0);
        QString strTemplateUuid = item->data(0,Qt::UserRole).toString();
        emit IconDel(stCatalogrName,nCatalogType,strTemplateUuid);
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
    newItem->setText(0,pIconMgr->getIconTemplate()->getSymbol()->getSymolName());
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

void HIconTreeWidget::initTemplateFile()
{
    if(!pIconMgr || !pIconMgr->getIconDocument())
        return;

    for(int i = 0; i < pIconMgr->getIconDocument()->pIconTemplateList.count();i++ )
    {
        HIconTemplate* pTemplate = (HIconTemplate*)pIconMgr->getIconDocument()->pIconTemplateList[i];
        if(!pTemplate) continue;
        HIconTreeWidgetItem* treeItem = findIconTreeWigetItem(pTemplate->getCatalogType());
        if(!treeItem) continue;

        QString strUuid =  pTemplate->getUuid().toString();
        HIconTreeWidgetItem* newItem = new HIconTreeWidgetItem(treeItem,TEMPLATE_TYPE_CHILD);
        if(!newItem) continue;
        newItem->setUuid(strUuid);
        newItem->setData(0,Qt::UserRole,QVariant(strUuid));
        newItem->setText(0,pTemplate->getSymbol()->getSymolName());
        treeItem->addChild(newItem);

        //collapseItem(treeItem);
    }
}

HIconTreeWidgetItem* HIconTreeWidget::findIconTreeWigetItem(int treeData)
{
    //int count = topLevelItemCount();
    int index = 0;
    while(index < topLevelItemCount())
    {
        HIconTreeWidgetItem* rootItem = static_cast<HIconTreeWidgetItem*>(topLevelItem(index));
        if(!rootItem) return NULL;
        for(int i = 0;i < rootItem->childCount();i++)
        {
            HIconTreeWidgetItem* childItem = static_cast<HIconTreeWidgetItem*>(rootItem->child(i));
            if(!childItem) continue;
            if(treeData == childItem->type())
                return childItem;
        }
        index++;
    }
    return NULL;
}

void HIconTreeWidget::expandIconItem(HIconTreeWidgetItem* item)
{
    int count = topLevelItemCount();
    for(int k = 0; k < count;k++)
    {
        HIconTreeWidgetItem* rootItem = static_cast<HIconTreeWidgetItem*>(topLevelItem(k));
        if(!rootItem) continue;
        for(int i = 0;i < rootItem->childCount();i++)
        {
            HIconTreeWidgetItem* childItem = static_cast<HIconTreeWidgetItem*>(rootItem->child(i));
            collapseItem(childItem);
        }
    }
    expandItem(item);
}
