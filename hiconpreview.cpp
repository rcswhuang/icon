#include "hiconpreview.h"
#include "ui_iconpreview.h"
#include "hicontemplate.h"
#include "hiconshowpattern.h"
#include "hbaseobj.h"
#include "hiconobj.h"
#include "hiconhelper.h"
#include <QIntValidator>
HIconPreview::HIconPreview(HIconMgr* iconMgr,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconPreview),pIconMgr(iconMgr)
{
    ui->setupUi(this);

    ui->widget->installEventFilter(this);
    ui->widthSpinBox->setRange(0,50);
    ui->heightSpinBox->setRange(0,50);

    connect(ui->widthSpinBox,SIGNAL(editingFinished()),this,SLOT(onDefaultSizeChanged()));
    connect(ui->heightSpinBox,SIGNAL(editingFinished()),this,SLOT(onDefaultSizeChanged()));
    connect(ui->refreshBtn,SIGNAL(clicked(bool)),this,SLOT(onRefreshChanged()));
}

HIconPreview::~HIconPreview()
{
    delete ui;
}

void HIconPreview::init()
{
    if(pIconMgr && pIconMgr->getIconTemplate())
    {
        QSizeF sizeF = pIconMgr->getIconTemplate()->getDefaultSize();
        ui->widthSpinBox->setValue(sizeF.width());
        ui->heightSpinBox->setValue(sizeF.height());
    }
    else
    {
        ui->widthSpinBox->setValue(0);
        ui->heightSpinBox->setValue(0);
    }
}

void HIconPreview::refresh()
{

    //p.drawLine(QPointF(0,0),QPoint(5,5));
    //drawIcon(&p);

}

void HIconPreview::onDefaultSizeChanged()
{
    int width = ui->widthSpinBox->value();
    int height = ui->heightSpinBox->value();
    if(pIconMgr && pIconMgr->getIconTemplate())
    {
        pIconMgr->getIconTemplate()->setDefaultSize(QSizeF(width,height));
        QRectF rectF = QRectF(-width*10,-height*10,width*20,height*20);
        pIconMgr->getIconFrame()->setLogicRect(rectF);
        onRefreshChanged();
    }
}

void HIconPreview::onRefreshChanged()
{
    if(!pIconMgr) return;
    HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
    if(!pTemplate) return;
    QSizeF tempSize = pTemplate->getDefaultSize();
    pixRect = QRectF(QPointF(0,0),tempSize);
    int nCurPattern = pTemplate->getSymbol()->getCurrentPattern();
    pixMap = HIconHelper::Instance()->iconPixmap(pTemplate->getCatalogName(),pTemplate->getUuid().toString(),tempSize,nCurPattern);
    QSize size = pixMap.size();
    ui->widget->update();//重绘操作
}

void HIconPreview::drawIcon(QPainter *p)
{
    HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
    if(!pTemplate) return;
    pixMap = HIconHelper::Instance()->iconPixmap(pTemplate->getCatalogName(),pTemplate->getUuid().toString());
}

bool HIconPreview::eventFilter(QObject *obj, QEvent *event)
{
    //return false;
    if(obj == ui->widget)
    {
        if(event->type() == QEvent::Paint)
        {
            if(!pixMap.isNull())
            {
                QPainter p(ui->widget);
                QPen pen(Qt::red);
                pen.setStyle(Qt::DotLine);
                p.setPen(pen);
                pixRect.moveCenter(QPointF(ui->widget->size().width()/2,ui->widget->size().height()/2));
                p.drawRect(pixRect);
                p.drawPixmap(pixRect.topLeft(),pixMap);

            }
            return true;
        }
    }

    return false;
}



