#ifndef HICONWIDGET_H
#define HICONWIDGET_H

#include <QWidget>
#include "hiconmgr.h"
class QTabBar;
class HIconFrame;
class QVBoxLayout;
class HIconWidget : public QWidget
{
    Q_OBJECT
public:
    HIconWidget(HIconMgr* iconMgr);
    void newIconWidget();
    void delIconWidget();
    void refreshIconWidget();


    QTabBar* getTabBar(){return pTabBar;}
    //HIconFrame* getIconFrame(){return pIconFrame;}
private:
    HIconMgr* pIconMgr;
    QTabBar* pTabBar;
    //HIconFrame* pIconFrame;
    QVBoxLayout* layout1;
};

#endif // HICONWIDGET_H
