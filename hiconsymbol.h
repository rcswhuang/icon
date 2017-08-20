﻿#ifndef HICONSYMBOL_H
#define HICONSYMBOL_H

#include <QObject>
#include <QtXml/QDomElement>
//存放每个一个图元内部的信息和图元本身的显示信息
#include "hbaseobj.h"
//#include "hiconshowpattern.h"
class HIconShowPattern;
class HIconTemplate;
class HIconSymbol:public QObject
{
public:
    HIconSymbol(QObject* parent = 0);
    ~HIconSymbol();

public:
    void readXml(QDomElement* dom);
    void writeXml(QDomElement *dom);

    //新建一个图元元素(按类型)
    HBaseObj* newObj(int nObjType);
    HBaseObj* newObj(QString tagName);

    //增加一个图元元素
    void addObj(HBaseObj* pObj);

    //删除一个图元元素
    void delObj(HBaseObj* pObj);

    void copyTo(HIconSymbol* isymbol);
    void setSymbolName(const QString& strName);
    QString getSymolName();

    void setIconSymbolWidth(double width);
    void setIconSymbolHeight(double height);


    int getObjID();
    bool findObjID(int nObjID);

    void updateShowPattern(QList<HBaseObj*> &list);
    //图元中多种状态的显示方案
    bool PatterIsValid(int nId);

    //新建
    HIconShowPattern* newPattern(const QString& name="");
    HIconShowPattern* newPattern(int id);

    //删除
    void delPattern(HIconShowPattern* sp);
    void delPattern(int id);
    void clearPattern();

    //查找和设置
    HIconShowPattern* findPatternById(int id);
    void setCurrentPattern(int id);
    int getCurrentPattern();
    int getCurrentPatternIndex();
    void setCurrentPatternPtr(HIconShowPattern* sp);
    HIconShowPattern* getCurrentPatternPtr();
    HIconTemplate* getIconTemplate()const {return pIconTemplate;}
public:
    //QList<HBaseObj*> pObjList;
    HIconTemplate* pIconTemplate;
    QVector<HIconShowPattern*> pShowPatternVector;
private:
    QString strSymbolName;
    int usSymbolType;
    int nMaxPattern;
    int nCurPattern;
    HIconShowPattern* pCurPattern;

};

#endif // HICONSYMBOL_H
