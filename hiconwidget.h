﻿#ifndef HICONWIDGET_H
#define HICONWIDGET_H

#include <QWidget>

#include "iconapi.h"
class QTabBar;
class HIconFrame;
class HIconMgr;
class HIconWidget : public QWidget
{
    Q_OBJECT
public:
    HIconWidget();

    void setIconMgr(HIconMgr* iconMgr);
    //新建一个icon图元
    void newIconWidget();

    //删除整个Icon的显示
    void delIconWidget();

    //刷新图元
    void refreshIconWidget();

    QTabBar* getTabBar(){return pTabBar;}

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    //HIconFrame* getIconFrame(){return pIconFrame;}
public slots:
    void addShowPattern();
    void delShowPattern();
    void renameShowPattern();
    void patternChanged(int curPatternId);
private:
    HIconMgr* pIconMgr;
    QTabBar* pTabBar;
};

#endif // HICONWIDGET_H
