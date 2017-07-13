#include "hframe.h"

/*
 * HFrame的坐标是主要在QMainWindow里面的中心区域，不包含左边框，上边菜单等状态的位置，最左边就是(0,0)
 * HGraphicsView的逻辑坐标则是包含在
*/
HFrame::HFrame(QWidget* parent, Qt::WindowFlags f):QFrame(parent,f)
{
    m_nHRulerHeight = 25;
    m_nVRulerWidth = 25;
    m_bIsShowRuler = true;
    m_fScale = 0.6;
    m_pView = new QGraphicsView(this);
    m_pView->setBackgroundRole(QPalette::Dark);
    m_pView->setCacheMode(QGraphicsView::CacheBackground);
    m_pView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_pView->setRubberBandSelectionMode(Qt::ContainsItemShape);
    m_pView->installEventFilter(this);
    m_pView->scale(m_fScale,m_fScale);
    m_pView->viewport()->setMouseTracking(true);
    m_pView->viewport()->installEventFilter(this);
    drawBox();

}

HFrame::~HFrame()
{

}

//设置显示标尺线
void HFrame::setShowRuler(bool bShow)
{
    if(bShow == m_bIsShowRuler)
        return;
    m_bIsShowRuler = bShow;
    if(bShow)
    {
        m_pView->move(m_nVRulerWidth,m_nHRulerHeight);
        m_pView->resize(width()-m_nVRulerWidth,height()-m_nHRulerHeight);
    }
    else
    {
        m_pView->move(0,0);
        m_pView->resize(width(),height());
    }
    update();
}

//获取显示标尺线
bool HFrame::isShowRuler()
{
    return m_bIsShowRuler;
}

//设置水平标尺线高度
void HFrame::setHRulerHeight(int height)
{

}

//获取水平标尺线高度
int  HFrame::hRulerHeight() const
{
    return m_nHRulerHeight;
}

//设置垂直标尺线宽度
void HFrame::setVRulerWidth(int width)
{

}

//获取垂直标尺线宽度
int  HFrame::vRulerWidth() const
{
    return m_nVRulerWidth;
}

//获取当前view
QGraphicsView* HFrame::view()
{
    return m_pView;
}

//获取比例
double HFrame::scale()
{
    return m_fScale;
}

//缩放到
void HFrame::scaleChangedTo(double scale)
{
    m_fScale = scale;
}

//缩放比例
void HFrame::scaleChanged(double ratio)
{

}

//移动中心点到view中间
void HFrame::centerOn(const QPointF& pos)
{

}

//水平滚动条改变
void HFrame::onHScrollBarChanged(int value)
{

}

//垂直滚动条改变
void HFrame::onVScrollBarChanded(int value)
{

}

//对象事件过滤
bool HFrame::eventFilter(QObject* obj,QEvent* event)
{
    if(obj == m_pView->viewport())
    {
        switch(event->type())
        {
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
            mouseMoved(((QMouseEvent*)event)->pos());
            return false;
        case QEvent::Resize:
            drawHRuler();
            update();
            return false;
        }
    }
    return false;
}

//绘制事件过滤
void HFrame::paintEvent(QPaintEvent* painterEvent)
{
    if(m_bIsShowRuler)
    {
        QPainter painter(this);
        painter.setBackground(QBrush(Qt::white));
        if(!m_vHRuler.isNull())
            painter.drawPixmap(m_nVRulerWidth,0,width()-m_nVRulerWidth,m_nHRulerHeight,m_vHRuler);
        if(!m_vBox.isNull())
            painter.drawPixmap(0,0,m_nVRulerWidth,m_nHRulerHeight,m_vBox);
    }

}

//大小改变事件过滤
void HFrame::resizeEvent(QResizeEvent* event)
{
    m_pView->move(m_nVRulerWidth,m_nHRulerHeight);
    int w = width() - m_nVRulerWidth;
    int h = height() - m_nHRulerHeight;
    m_pView->resize(w-1,h-1);
    m_pView->resize(w,h);
}

//绘制水平标尺
void HFrame::drawHRuler()
{
    //m_vHRuler
    m_vHRuler = QPixmap(width()-m_nVRulerWidth,m_nHRulerHeight);
    m_vHRuler.fill();
    //QPainter painter(&m_vHRuler);
    //painter.save();
}

//绘制垂直标尺
void HFrame::drawVRuler()
{

}

//绘制左上角
void HFrame::drawBox()
{
    m_vBox = QPixmap(m_nVRulerWidth,m_nHRulerHeight);
    m_vBox.fill();
    QPainter painter(&m_vBox);
    //painter.save();
    painter.setPen(Qt::DashLine);
    painter.drawLine(m_nVRulerWidth/2-1,0,m_nVRulerWidth/2-1,m_nHRulerHeight);
    painter.drawLine(0,m_nHRulerHeight/2-1,m_nVRulerWidth,m_nHRulerHeight/2-1);

    painter.setPen(Qt::white);
    painter.drawLine(0,1,0,m_nHRulerHeight+1);
    painter.drawLine(1,0,m_nVRulerWidth,0);

    painter.setPen(Qt::darkGray);
    painter.drawLine(0,m_nHRulerHeight-1,m_nVRulerWidth,m_nHRulerHeight-1);
    painter.drawLine(m_nVRulerWidth-1,0,m_nVRulerWidth-1,m_nHRulerHeight);

    //painter.restore();

}

//鼠标位置改变
void HFrame:: mouseMoved(const QPoint& pos)
{
    //pos的位置就是Frame的坐标，也就是pView的坐标系统
    //Scene的坐标就是(500,500)起始点
    m_vCurpos = pos;
    QPointF logPos = m_pView->mapToScene(pos);//转换成Secne的坐标系统
    emit mousePosChanged(pos,logPos);
}
