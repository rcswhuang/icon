﻿#ifndef HICONSCENE_H
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
class HIconSelectionItem;
class HIconScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HIconScene(HIconMgr* iconMgr);
public:
    //移动到顶层
    void bringToTop();
    //移动到底层
    void bringToBottom();
    bool getItemAt(const QPointF& pos);
    void setItemProperty(QGraphicsItem *item);
    void setItemCursor(QGraphicsSceneMouseEvent *mouseEvent);
    void addItemByPatternId(int nPatternId);
    void delItemByPatternId(int nPatternId);
    void setItemVisible(int nPatternId);
    void calcSelectedItem(const QRectF& rectF);
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);
    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

signals:
    void itemInserted(int type);
    void itemSelected(QGraphicsItem* item);
public slots:
    void cutItem();
    void copyItem();
    void delItem();
    //void showPattern();
    void showProperty();
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
    HIconSelectionItem* select;
    //HIconRectItem

};

#endif // HGRAPHICSSCENE_H
