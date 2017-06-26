#ifndef HICONSCENE_H
#define HICONSCENE_H

#include <QGraphicsScene>
#include "hevent.h"

class HIconFrame;
class HIconMgr;
class HIconLineItem;
class HIconRectItem;
class HIconEllipseItem;
class HIconPolygonItem;
class HIconArcItem;
class HIconPieItem;
class HIconTextItem;
class HIconScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HIconScene(HIconMgr* iconMgr);

protected:

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);

signals:
    void itemInserted(int type);
    void itemSelected(QGraphicsItem* item);
private:
    HIconMgr* pIconMgr;
    HIconFrame* pIconFrame;
    HIconLineItem* line;
    HIconRectItem* rectangle;
    HIconEllipseItem* ellipse;
    HIconPolygonItem* polygon;
    HIconArcItem* arc;
    HIconPieItem* pie;
    HIconTextItem* text;

};

#endif // HGRAPHICSSCENE_H
