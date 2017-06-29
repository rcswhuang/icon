#include "hdrawtool.h"
#include "hiconstate.h"

QList<HDrawTool*> HDrawTool::drawToolList;

static HSelectTool selectTool;
static HRectTool rectTool(enumRectangle);
static HRectTool ellipseTool(enumEllipse);
static HRectTool arcTool(enumArc);
static HRectTool pieTool(enumPie);
static HRectTool textTool(enumText);
static HLineTool lineTool(enumLine);



HDrawTool* HDrawTool::findTool( DRAWSHAPE drawShape )
{
    QList<HDrawTool*>::iterator it;
    for(it = drawToolList.begin(); it != drawToolList.end();++it)
    {
        HDrawTool *drawTool = dynamic_cast<HDrawTool*>(*it);
        if(drawTool->m_drawShape == drawShape)
            return drawTool;
    }
    return NULL;
}

QPointF HDrawTool::c_down;
quint32 HDrawTool::c_nDownFlags;
QPointF HDrawTool::c_last;
DRAWSHAPE HDrawTool::c_drawShape = enumSelection;

HDrawTool::HDrawTool(DRAWSHAPE drawShape)
{
    m_drawShape = drawShape;
    drawTool.append(this);
}

void HDrawTool::mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{
    c_down = event->scenePos();
    c_last = event->scenePos();
}

void HDrawTool::mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{
    c_last = event->pos();
    //setCursor()
}

void HDrawTool::mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{
    if(event->scenePos() == c_down)
        m_drawShape = enumSelection;
}


HSelectTool::HSelectTool():HDrawTool(enumSelection)
{

}

// Implementation
void HSelectTool::mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HSelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HSelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HSelectTool::OnEditProperties(HIconScene * scene)
{

}

void HSelectTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene)
{

}



HRectTool::HRectTool(DRAWSHAPE drawShape)
{

}

// Implementation
void HRectTool::mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HRectTool::mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HRectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HRectTool::OnEditProperties(HIconScene * scene)
{

}



HLineTool::HLineTool(DRAWSHAPE drawShape)
{

}

// Implementation
void HLineTool::mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HLineTool::mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HLineTool::mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene )
{

}

void HLineTool::OnEditProperties(HIconScene * scene)
{

}









