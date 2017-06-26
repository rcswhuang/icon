#ifndef HDRAWTOOL_H
#define HDRAWTOOL_H

#include <QObject>
#include "iconapi.h"
//绘制工具基类
#include "hevent.h"
class HIconState;

class HDrawTool
{
public:
    HDrawTool(HIconState* iconState,DRAWSHAPE drawShape,const QString& IconName,const QString& iconType,const QString& uuid);
    virtual ~HDrawTool();
public:
    virtual DRAWSHAPE type() = 0;
    virtual void clear();
    virtual void OnEvent(HEvent &e);

    QString iconType() {return strIconType;}
    QString Uuid() {return strUuid;}
    HIconState* IconState(){return pIconState;}
    DRAWSHAPE DrawShape(){return enDrawShape;}

protected:
    HIconState* pIconState;
    DRAWSHAPE enDrawShape;//绘制的对象：直线 圆形
    QString strIconType;//模板的类型：遥测
    QString strUuid;//模板的id
    QString strIconName;
};

#endif // HDRAWTOOL_H
