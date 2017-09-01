#ifndef HICONSCENE_H
#define HICONSCENE_H

#include <QGraphicsScene>
class HIconFrame;
class HIconMgr;
class HIconLineItem;
class HIconRectItem;
class HIconEllipseItem;
class HIconCircleItem;
class HIconPolygonItem;
class HIconArcItem;
class HIconPieItem;
class HIconTextItem;
class HIconSelectionItem;
class HIconGraphicsItem;
class HBaseObj;
class HIconScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HIconScene(HIconMgr* iconMgr);
public:
    void bringToTop();
    void bringToBottom();
    bool getItemAt(const QPointF& pos);
    void setItemProperty(QGraphicsItem *item);
    void setItemCursor(QGraphicsSceneMouseEvent *mouseEvent);
    HIconGraphicsItem* addItemByIconObj(int nPattern,HBaseObj* pObj);
    void addItemByPatternId(int nPatternId);
    void delItemByPatternId(int nPatternId);
    void setItemVisible(int nPatternId);
    void calcSelectedItem(const QRectF& rectF);
    int pointInRect(QPointF& pointF);
    void prepareMoveItem(QGraphicsSceneMouseEvent *mouseEvent);
    void prepareRezieItem(QGraphicsSceneMouseEvent *mouseEvent);
    void addNewIconCommand(HBaseObj* pObj);
    void getIconGraphicsItemPointList(HIconGraphicsItem* item,QList<QPolygonF>& pfList);
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
    void pasteItem();
    void showProperty();
private:
    int nSelectMode;
    bool bLeftShift;
    QPointF prePoint;
    QPointF curPoint;
    QList<QPolygonF> oldPolygonF;
    QList<QPolygonF> newPolygonF;

    HIconMgr* pIconMgr;
    HIconLineItem* line;
    HIconRectItem* rectangle;
    HIconEllipseItem* ellipse;
    HIconCircleItem* circle;
    HIconPolygonItem* polygon;
    HIconArcItem* arc;
    HIconPieItem* pie;
    HIconTextItem* text;
    HIconSelectionItem* select;
    //HIconRectItem

};

#endif // HGRAPHICSSCENE_H
