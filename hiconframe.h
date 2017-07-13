#ifndef HICONFRAME_H
#define HICONFRAME_H
#include "hframe.h"
#include "hiconscene.h"
#include <QWidget>
#include <QRectF>
#include <QResizeEvent>
#include "hbaseobj.h"


class HIconMgr;
struct Path;
class HIconFrame : public HFrame
{
    Q_OBJECT
public:
    HIconFrame(QWidget * parent = 0, Qt::WindowFlags f = 0 );
    HIconFrame(HIconMgr* pMgr,QWidget * parent = 0, Qt::WindowFlags f = 0 );
    ~HIconFrame();

public:

    void setIconMgr(HIconMgr* iconmgr);
    //绘制路径
    void drawPath(const QList<Path>& pathList);

    //结束绘制
    void endDraw();

    //对象的创建
    void objCreated(HBaseObj* obj);

    //对象的删除
    //void objRemoved(HDrawObj* obj);

    //刷新选中点、选中框
    void refreshSelected(const QRectF& rect);

    //鼠标的改变
    void cursorChanged(const QCursor& cursor);

    //合适宽度
    void fitWidth();

    //合适高度
    void fitHeight();

    void setLogicRect(QRectF& rectF);

    void delItemByPatternId(int nPatternId);

    QRectF getLogicRect(){return sceneRect;}

    HIconScene* iconScene();


    void setItemVisible(int nPatternId);
public slots:


protected:

    //事件过滤
    virtual bool eventFilter( QObject *obj, QEvent *event);//过滤的对象，过滤的事件

private:
    QRectF sceneRect;
    HIconMgr* pIconMgr;

};

#endif // HICONFRAME_H
