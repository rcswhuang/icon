#include "hiconbrower.h"
#include "hicontreewidget.h"
#include <QVBoxLayout>
HIconBrower::HIconBrower(QWidget* parent):QWidget(parent)
{
    init();
}

void HIconBrower::init()
{
    pIconTreeWidget = new HIconTreeWidget(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(pIconTreeWidget);
    setLayout(layout);
    pIconTreeWidget->init();
}

void HIconBrower::newIcon(const QString& strName,const int& nIconType)
{

    emit IconNew(strName,nIconType);
}
