﻿#ifndef HICONTREEWIDGET_H
#define HICONTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QContextMenuEvent>
#include <QAction>
#include <QUuid>
#include "hiconapi.h"
#include "hicontemplate.h"
#include "hiconbrower.h"
class HIconMgr;
/*
 测点
  |-遥信
     |--开关(HIconTemplate->HIconSymbol)
         |-开关分（showPattern)
         |-开关合
         |-开关双位置分错
         |-开关双位置合错
  |-遥测
  |-光字牌
  |-遥控
  |-遥脉
  |-档位
*/

//#define ICON_TYPE_DIGITAL 0x001
//#define


class HIconTreeWidgetItem : public QTreeWidgetItem
{
public:
    HIconTreeWidgetItem(HIconTreeWidget* parent = 0,int type = QTreeWidgetItem::UserType);
    HIconTreeWidgetItem(HIconTreeWidgetItem* parent = 0,int type = QTreeWidgetItem::UserType);
    void setUuid(QString uuid);
    QString getUuid();
private:
    QString strUuid;

};

class HIconTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    HIconTreeWidget(HIconMgr* iconMgr,QWidget* parent = 0,int type = QTreeWidgetItem::UserType);
    ~HIconTreeWidget();
public:
    void init();
    void initTemplateFile();
    void initTemplateMenu(QContextMenuEvent *event);
    void initTemplateChildMenu(QContextMenuEvent* event);
    void addIconTreeWigetItem();
    void delIconTreeWidgetItem();
    HIconTreeWidgetItem* findIconTreeWigetItem(int treeData);
    void expandIconItem(HIconTreeWidgetItem* item);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void IconNew(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void IconDel(const QString& strCatalogName,const int& nCatalogType,const QString& strUuid);
    void IconOpen(const QString& strCatalogName,const int& nCatalogType,const QString& strUuid);
public slots:
    void newIcon();
    void deleteIcon();
    void renameIcon();
    void importIcon();
    void openIcon(QTreeWidgetItem*,int);

public:
    HIconTreeWidgetItem* digitalItem;
    HIconTreeWidgetItem* analogueItem;
    HIconTreeWidgetItem* lightItem;
    HIconTreeWidgetItem* controlItem;
    HIconTreeWidgetItem* pulseItem;//遥脉
    HIconTreeWidgetItem* tapItem;
    HIconTreeWidgetItem* paiItem;
private:
    QAction* newAct;
    QAction* delAct;
    QAction* renameAct;
    QAction* importAct;

    HIconMgr* pIconMgr;
};

#endif // HICONTREEWIDGET_H
