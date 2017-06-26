#include "hiconwidget.h"
#include <QVBoxLayout>
#include "hiconframe.h"
#include <QTabBar>
HIconWidget::HIconWidget(HIconMgr* iconMgr):pIconMgr(iconMgr)
{
    pTabBar = new QTabBar;
    layout1 = new QVBoxLayout;
    layout1->setContentsMargins(0,0,0,0);
    layout1->setSpacing(0);
    setLayout(layout1);
}

void HIconWidget::newIconWidget()
{
    pTabBar->addTab(QStringLiteral("缺省"));
    layout1->addWidget(pTabBar);
    pTabBar->show();
    layout1->addWidget(pIconMgr->getIconFrame());
    pIconMgr->getIconFrame()->show();
}

void HIconWidget::delIconWidget()
{

    if(pTabBar)
    {
        int tabBarCount = pTabBar->count();
        while (tabBarCount--) {
            pTabBar->removeTab(tabBarCount);
        }
    }
    if(layout1)
    {
        layout1->removeWidget(pTabBar);
        layout1->removeWidget(pIconMgr->getIconFrame());
        pTabBar->hide();
        pIconMgr->getIconFrame()->hide();
    }
}

void HIconWidget::refreshIconWidget()
{

}
