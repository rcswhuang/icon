#include "hiconpreview.h"
#include "ui_iconpreview.h"
#include "hicontemplate.h"
#include "hbaseobj.h"
#include "hiconobj.h"
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

   // QTimer *timer = new QTimer(this);
  //  connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
  //  timer->start(5000);
    if(pIconMgr && pIconMgr->getIconTemplate())
    {
        QSizeF sizeF = pIconMgr->getIconTemplate()->getDefaultSize();
        ui->widthSpinBox->setValue(sizeF.width());
        ui->heightSpinBox->setValue(sizeF.height());
    }

}

HIconPreview::~HIconPreview()
{
    delete ui;
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
    }
}

void HIconPreview::onRefreshChanged()
{
    if(!pIconMgr) return;
    HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
    if(!pTemplate) return;
    QSizeF tempSize = pTemplate->getDefaultSize();
    pixRect = QRectF(QPointF(0,0),tempSize);
    QSize sz = ui->widget->size();
    pixRect.moveCenter(QPointF(ui->widget->size().width()/2,ui->widget->size().height()/2));

    pixMap = QPixmap(ui->widget->size());
    if(pixMap.isNull()) return;
    QPainter p(&pixMap);
    p.setRenderHint(QPainter::Antialiasing,true);
    p.fillRect(QRect(QPoint(0,0),ui->widget->size()),Qt::white);
    p.save();
    p.setPen(QPen(Qt::DotLine));
    p.drawRect(pixRect);
    p.restore();
    drawIcon(&p);
    ui->widget->update();//重绘操作
}

void HIconPreview::drawIcon(QPainter *p)
{
    HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
    if(!pTemplate) return;
    HIconSymbol* pSymbol = pTemplate->getSymbol();
    if(!pSymbol) return;
    qreal deltaX = pixRect.width()/pIconMgr->getLogicRect().width();
    qreal deltaY = pixRect.height()/pIconMgr->getLogicRect().height();
    p->save();
    p->translate(ui->widget->size().width()/2,ui->widget->size().height()/2);
    QPen pen(Qt::NoPen);
    QList<HBaseObj*>::iterator it;
    for(it = pSymbol->pObjList.begin();it!=pSymbol->pObjList.end();++it)
    {
        HBaseObj* pObj = (HBaseObj*)*it;
        pen.setColor(QColor(pObj->getLineColorName()));
        pen.setWidth(1);
        pen.setStyle(pObj->getLineStyle());
        if(pObj->getFrameSee())
            p->setPen(pen);
        else
            p->setPen(Qt::NoPen);

        quint8 nFillWay = pObj->getFillWay();//填充选择
        quint8 nFillStyle = pObj->getFillStyle(); //填充风格
        quint8 nTransparency = pObj->getTransparency(); //透明度
        quint8 nFillDir = pObj->getFillDirection();//填充方向
        QColor fillClr = QColor(pObj->getFillColorName());//填充颜色
        //quint8 nFillPercentage = pRectObj->getFillPercentage(); //填充比例
        QBrush brush;

        if(nFillWay >= 1)
        {
            p->setOpacity(1-(qreal)nTransparency/100.00);
            if(nFillStyle == Qt::LinearGradientPattern)
            {
                QPointF ps1,ps2;
               /* switch(nFillDir)
                {
                    case DIRECT_BOTTOM_TO_TOP:
                    {
                        ps2 = rect().topLeft();
                        ps1 = rect().bottomLeft();
                        break;
                    }
                    case DIRECT_TOP_TO_BOTTOM: //有顶到底
                    {
                        ps1 = rect().topLeft();
                        ps2 = rect().bottomLeft();
                        break;
                    }
                    case DIRECT_LEFT_TO_RIGHT: //由左到右
                    {
                        ps1 = rect().topLeft();
                        ps2 = rect().topRight();
                        break;
                    }
                    case DIRECT_RIGHT_TO_LEFT: //由右到左
                    {
                        ps1 = rect().topRight();
                        ps2 = rect().topLeft();
                        break;
                    }
                    case DIRECT_VER_TO_OUT: //垂直到外
                    {
                        ps1 = QPointF(rect().center().x(),rect().top());
                        ps2 = rect().topLeft();
                        break;
                    }
                    case DIRECT_HORi_TO_OUT: //水平向外
                    {
                        ps1 = QPointF(rect().left(),rect().center().y());
                        ps2 = rect().topLeft();
                        break;
                    }
                    case DIRECT_VER_TO_IN: //垂直向里
                    {
                        ps2 = QPointF(rect().center().x(),rect().top());
                        ps1 = rect().topLeft();
                        break;
                    }
                    case DIRECT_HORI_TO_IN: //垂直向里
                    {
                        ps2 = QPointF(rect().left(),rect().center().y());
                        ps1 = rect().topLeft();
                        break;
                    }
                }
                QLinearGradient lgrd(ps1,ps2);
                lgrd.setColorAt(0.0,fillClr);
                lgrd.setColorAt(0.5,fillClr.lighter(150));
                lgrd.setColorAt(1.0,fillClr.lighter(250));
                lgrd.setSpread(QGradient::ReflectSpread);
                QBrush brush2(lgrd);
                brush = brush2;
                //painter->setBrush(brush2);
                //painter->drawRect(rect());*/
            }
            else if(nFillStyle == Qt::RadialGradientPattern)
            {
                /*QRadialGradient lgrd(rect().center(),qMin(rect().width(),rect().height())/2);
                lgrd.setColorAt(0.0,fillClr);
                lgrd.setColorAt(0.5,fillClr.dark(150));
                lgrd.setColorAt(1.0,fillClr.dark(250));
                lgrd.setSpread(QGradient::ReflectSpread);
                QBrush brush2(lgrd);
                brush = brush2;*/
            }
            else if(nFillStyle == Qt::ConicalGradientPattern)
            {
                /*QConicalGradient lgrd(rect().center(),270);
                lgrd.setColorAt(0.0,fillClr);
                lgrd.setColorAt(0.5,fillClr.lighter(150));
                lgrd.setColorAt(1.0,fillClr.lighter(250));
                lgrd.setSpread(QGradient::ReflectSpread);
                QBrush brush2(lgrd);
                brush = brush2;*/
            }
            else
            {
                Qt::BrushStyle bs = (Qt::BrushStyle)nFillStyle;
                QBrush brush1(fillClr,bs);
                brush = brush1;
                //painter->setBrush(brush);
            }
           // qreal top = rect().top()*(float)(nFillPercentage/100.00);
           // drawRectF.setTop(top);
        }
        p->setBrush(brush);
        DRAWSHAPE shapeType = pObj->getShapeType();
        if(shapeType == enumLine)
        {
            HLineObj* pLineObj = (HLineObj*)pObj;
            p->drawLine(pLineObj->pfHeadPoint,pLineObj->pfTailPoint);
        }
        else if(shapeType == enumEllipse)
        {
            HEllipseObj* pEllipseObj = (HEllipseObj*)pObj;
            //deltaX = pixRect.width()/pEllipseObj->rectWidth;
            //deltaY = pixRect.height()/pEllipseObj->rectHeight;
            QPointF pt = QPointF(pEllipseObj->topLeft.x()*deltaX,pEllipseObj->topLeft.y()*deltaY);
            p->drawEllipse(QRectF(pt,QSizeF(pEllipseObj->rectWidth*deltaX,pEllipseObj->rectHeight*deltaY)));
            //p->drawEllipse(QRectF(QPointF(0,0),QSizeF(5,5)));
        }
        else if(shapeType == enumRectangle)
        {
            HRectObj* pRectObj = (HRectObj*)pObj;
            //p->drawRect(QRectF(QPoint(pRectObj->rectLeft,pRectObj->rectTop),QSizeF(pRectObj->rectWidth,pRectObj->rectHeight)));
        }


    }
    p->restore();
}

bool HIconPreview::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->widget)
    {
        if(event->type() == QEvent::Paint)
        {
            if(!pixMap.isNull())
            {
                QPainter p(ui->widget);
                p.drawPixmap(QPoint(0,0),pixMap);
            }
            return true;
        }
    }

    return false;
}



