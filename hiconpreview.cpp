#include "hiconpreview.h"
#include "ui_iconpreview.h"
#include "hicontemplate.h"
#include "hbaseobj.h"
#include "hiconobj.h"
#include "hiconshowpattern.h"
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
    pixRect = QRectF(QPointF(0,0),tempSize*2);
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
    //pIconMgr->getIconFrame()->view()->render(&p);
    //pIconMgr->getIconFrame()->iconScene()->render(&p,pIconMgr->getIconFrame()->getLogicRect(),pixRect);

    drawIcon(&p);
    ui->widget->update();//重绘操作
}

void HIconPreview::drawIcon(QPainter *p)
{
    HIconTemplate* pTemplate = pIconMgr->getIconTemplate();
    if(!pTemplate) return;
    HIconShowPattern* pShowPattern = pTemplate->getSymbol()->getCurrentPatternPtr();
    if(!pShowPattern) return;
    qreal deltaX = pixRect.width()/pIconMgr->getIconFrame()->getLogicRect().width();
    qreal deltaY = pixRect.height()/pIconMgr->getIconFrame()->getLogicRect().height();
    p->save();
    p->translate(ui->widget->size().width()/2,ui->widget->size().height()/2);
    QPen pen(Qt::NoPen);
    QList<HBaseObj*>::iterator it;
    for(it = pShowPattern->pObjList.begin();it != pShowPattern->pObjList.end();++it)
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
        QBrush brush;

        if(nFillWay >= 1)
        {
            p->setOpacity(1-(qreal)nTransparency/100.00);
            if(nFillStyle == Qt::LinearGradientPattern)
            {
                QPointF ps1,ps2;
                switch(nFillDir)
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
            }
            else if(nFillStyle == Qt::RadialGradientPattern)
            {
                QRadialGradient lgrd(rect().center(),qMin(rect().width(),rect().height())/2);
                lgrd.setColorAt(0.0,fillClr);
                lgrd.setColorAt(0.5,fillClr.dark(150));
                lgrd.setColorAt(1.0,fillClr.dark(250));
                lgrd.setSpread(QGradient::ReflectSpread);
                QBrush brush2(lgrd);
                brush = brush2;
            }
            else if(nFillStyle == Qt::ConicalGradientPattern)
            {
                QConicalGradient lgrd(rect().center(),270);
                lgrd.setColorAt(0.0,fillClr);
                lgrd.setColorAt(0.5,fillClr.lighter(150));
                lgrd.setColorAt(1.0,fillClr.lighter(250));
                lgrd.setSpread(QGradient::ReflectSpread);
                QBrush brush2(lgrd);
                brush = brush2;
            }
            else
            {
                Qt::BrushStyle bs = (Qt::BrushStyle)nFillStyle;
                QBrush brush1(fillClr,bs);
                brush = brush1;
            }
        }
        p->setBrush(brush);
        DRAWSHAPE shapeType = pObj->getShapeType();
        if(shapeType == enumLine)
        {
            HLineObj* pLineObj = (HLineObj*)pObj;
            QPointF pt1 = QPointF(pLineObj->pfHeadPoint.x()*deltaX,pLineObj->pfHeadPoint.y()*deltaY);
            QPointF pt2 = QPointF(pLineObj->pfTailPoint.x()*deltaX,pLineObj->pfTailPoint.y()*deltaY);
            p->drawLine(pt1,pt2);
        }
        else if(shapeType == enumEllipse)
        {
            HEllipseObj* pEllipseObj = (HEllipseObj*)pObj;
            QPointF pt = QPointF(pEllipseObj->topLeft.x()*deltaX,pEllipseObj->topLeft.y()*deltaY);
            p->drawEllipse(QRectF(pt,QSizeF(pEllipseObj->rectWidth*deltaX,pEllipseObj->rectHeight*deltaY)));
        }
        else if(shapeType == enumRectangle)
        {
            HRectObj* pRectObj = (HRectObj*)pObj;
            QPointF pt = QPointF(pRectObj->topLeft.x()*deltaX,pRectObj->topLeft.y()*deltaY);
            p->drawRect(QRectF(pt,QSizeF(pRectObj->rectWidth*deltaX,pRectObj->rectHeight*deltaY)));
        }
        else if(shapeType == enumCircle)
        {
            HCircleObj* pCircleObj = (HCircleObj*)pObj;
            QPointF pt = QPointF(pCircleObj->topLeft.x()*deltaX,pCircleObj->topLeft.y()*deltaY);
            p->drawEllipse(QRectF(pt,QSizeF(pCircleObj->rectWidth*deltaX,pCircleObj->rectHeight*deltaY)));
        }
        else if(shapeType == enumPolyline)
        {
            HPolylineObj* pPolylineObj = (HPolylineObj*)pObj;
            QPolygonF pyTempList;
            foreach(QPointF pt,pPolylineObj->pylist)
                pyTempList<<QPointF(pt.x()*deltaX,pt.y()*deltaY);
            //p->drawPolygon(pyTempList);
            QPolygonF polygon(pyTempList);
            QPainterPath path;
            path.moveTo(polygon.at(0));
            for(int i = 1; i < polygon.size();i++)
                path.lineTo(polygon.at(i));
            p->drawPath(path);
        }
        else if(shapeType == enumPolygon)
        {
            HPolygonObj* pPolyObj = (HPolygonObj*)pObj;
            QPolygonF pyTempList;
            foreach(QPointF pt,pPolyObj->pylist)
                pyTempList<<QPointF(pt.x()*deltaX,pt.y()*deltaY);
            p->drawPolygon(pyTempList);
        }
        else if(shapeType == enumArc)
        {
            HArcObj* pArcObj = (HArcObj*)pObj;
            QPointF pt = QPointF(pArcObj->topLeft.x()*deltaX,pArcObj->topLeft.y()*deltaY);
            if(pArcObj->bCloseCheck)
                p->drawChord(QRectF(pt,QSizeF(pArcObj->rectWidth*deltaX,pArcObj->rectHeight*deltaY)),pArcObj->startAngle*16,pArcObj->spanAngle*16);
            else
                p->drawArc(QRectF(pt,QSizeF(pArcObj->rectWidth*deltaX,pArcObj->rectHeight*deltaY)),pArcObj->startAngle*16,pArcObj->spanAngle*16);
        }
        else if(shapeType == enumPie)
        {
            HPieObj* pPieObj = (HPieObj*)pObj;
            QPointF pt = QPointF(pPieObj->topLeft.x()*deltaX,pPieObj->topLeft.y()*deltaY);
            p->drawPie(QRectF(pt,QSizeF(pPieObj->rectWidth*deltaX,pPieObj->rectHeight*deltaY)),pPieObj->startAngle*16,pPieObj->spanAngle*16);
        }
        else if(shapeType == enumText)
        {
            HTextObj* pTextObj = (HTextObj*)pObj;
            QString strFontName = pTextObj->getTextFontName();
            int pointSize = pTextObj->getPointSize();

            int weight = pTextObj->getWeigth();
            bool italic = pTextObj->getItalic();
            QFont font(strFontName,pointSize,weight,italic);

            QPen textPen = QPen(QColor(pTextObj->getTextColorName()));
            p->setPen(textPen);
            p->setFont(font);
            QPointF pt = QPointF(pTextObj->getTopLeftPoint().x()*deltaX,pTextObj->getTopLeftPoint().y()*deltaY);
            int nAlign = pTextObj->getHorizontalAlign()|pTextObj->getVerticalAlign();
            p->drawText(QRectF(pt,QSizeF(pTextObj->getRectWidth()*deltaX,pTextObj->getRectHeight()*deltaY)),nAlign,pTextObj->getTextContent());
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



