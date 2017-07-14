#ifndef HDRAWTOOL_H
#define HDRAWTOOL_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <hiconscene.h>
#include "hiconapi.h"
//绘制工具基类
//class HIconState;

class HDrawTool
{
public:
    HDrawTool(DRAWSHAPE drawShape);

public:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene );

   DRAWSHAPE m_drawShape;
   static HDrawTool * findTool( DRAWSHAPE drawShape );
   static QList<HDrawTool*> drawToolList;
   static QPointF c_down;
   static quint32 c_nDownFlags;
   static QPointF c_last;
   static DRAWSHAPE c_drawShape;

};

class HSelectTool : public HDrawTool
{
// Constructors
public:
    HSelectTool();

// Implementation
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene );
    virtual void OnEditProperties(HIconScene * scene);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene);
};

class HRectTool : public HDrawTool
{
// Constructors
public:
    HRectTool(DRAWSHAPE drawShape);

// Implementation
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene );
    virtual void OnEditProperties(HIconScene * scene);
};

class HLineTool : public HDrawTool
{
// Constructors
public:
    HLineTool(DRAWSHAPE drawShape);

// Implementation
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , HIconScene * scene );
    virtual void OnEditProperties(HIconScene * scene);
};





/*
class CPolyTool : public CDrawTool
{
// Constructors
public:
    CPolyTool();

// Implementation
    virtual void OnLButtonDown(CRCSRuleEditorView* pView, UINT nFlags, const CPoint& point);
    virtual void OnLButtonDblClk(CRCSRuleEditorView* pView, UINT nFlags, const CPoint& point);
    virtual void OnLButtonUp(CRCSRuleEditorView* pView, UINT nFlags, const CPoint& point);
    virtual void OnMouseMove(CRCSRuleEditorView* pView, UINT nFlags, const CPoint& point);
    virtual void OnCancel();

    CDrawPoly* m_pDrawObj;
};
*/

#endif // HDRAWTOOL_H
