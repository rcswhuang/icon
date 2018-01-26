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

    //刷新选中点、选中框
    void refreshSelected(const QRectF& rect);

    //鼠标的改变
    void cursorChanged(const QCursor& cursor);

    //合适宽度
    void fitWidth();

    //合适高度
    void fitHeight();

    //剪切
    void cut();

    //复制
    void copy();

    //粘贴
    void paste();

    void del();

    //移动到顶层
    void bringToTop();

    //移动到底层
    void bringToBottom();

    //组合
    void groupObj();

    //取消组合
    void ungroupObj();

    //设置scene的逻辑区域
    void setLogicRect(QRectF& rectF);

    //在pattern增加Item对象
    HIconGraphicsItem* addItemByIconObj(int nPattern,HBaseObj* pObj);

    //增加scene的显示方案
    void addItemByPatternId(int nPatternId);

    //删除scene的显示方案
    void delItemByPatternId(int nPatternId);

    //获取scene的区域
    QRectF getLogicRect();

    //获取frame里面的scene对象
    HIconScene* iconScene();

    //设置显示方案对象的显示和隐藏功能
    void setItemVisible(int nPatternId);

    QString getClipboardFile();

    //获取item
    HIconGraphicsItem* getIconGraphicsItemByObj(HBaseObj* pObj);


public slots:


protected:

    //事件过滤
   // virtual bool eventFilter( QObject *obj, QEvent *event);//过滤的对象，过滤的事件

private:
    QRectF sceneRect;
    HIconMgr* pIconMgr;

};

#endif // HICONFRAME_H
