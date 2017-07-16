#ifndef HICONOBJ_H_
#define HICONOBJ_H_
#include "hbaseobj.h"
class HIconLineItem;
class HLineObj : public HBaseObj
{
public:
    HLineObj();
    ~HLineObj();

    //二进制读写
    virtual void readData(QDataStream* data);
    virtual void writeData(QDataStream* data);

    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);
    virtual HLineObj* clone();

    virtual DRAWSHAPE getShapeType();

public:

    void setArrowStart(quint8 start);
    quint8 getArrowStart();

    void setArrowEnd(quint8 end);
    quint8 getArrowEnd();

    void setArrowWidth(quint16 width);
    quint16 getArrowWidth();

    void setArrowHeight(quint16 height);
    quint16 getArrowHeight();

private:
    quint8 arrowStart;
    quint8 arrowEnd;
    quint16 arrowWidth;
    quint16 arrowHeight;
public:
    QPointF pfHeadPoint;
    QPointF pfTailPoint;
};

class HRectObj : public HBaseObj
{
public:
    HRectObj();
    virtual ~HRectObj();
    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DRAWSHAPE getShapeType();

public:
    QPointF topLeft;
    //QPointF rectTop;
    double rectWidth;
    double rectHeight;
};


class HEllipseObj : public HBaseObj
{
public:
    HEllipseObj();
    virtual ~HEllipseObj();
    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();
    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DRAWSHAPE getShapeType();

public:
    QPointF topLeft;
    //QPointF rectTop;
    double rectWidth;
    double rectHeight;
};


class HPolygonObj : public HBaseObj
{
public:
    HPolygonObj();
    virtual ~HPolygonObj();
    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();
    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DRAWSHAPE getShapeType();

public:
   QVector<QPointF> pylist;
};

class HArcObj : public HBaseObj
{
public:
    HArcObj();
    virtual ~HArcObj();
    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();

    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DRAWSHAPE getShapeType();

public:
    void setStartAngle(int sAngle);
    int getStartAngle();
    void setSpanAngle(int spanangle);
    int getSpanAngle();
    void setCloseStatus(bool bcheck);
    bool getCloseStatus();
public:
    QPointF topLeft;
    //QPointF rectTop;
    double rectWidth;
    double rectHeight;
    int startAngle;//其实角度
    int spanAngle;//旋转角度
    bool bCloseCheck;
};


class HPieObj : public HBaseObj
{
public:
    HPieObj();
    virtual ~HPieObj();
    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();
    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DRAWSHAPE getShapeType();

public:
    void setStartAngle(int sAngle);
    int getStartAngle();
    void setSpanAngle(int spanangle);
    int getSpanAngle();
    void setCloseStatus(bool bcheck);
    bool getCloseStatus();
public:
    QPointF topLeft;
    //QPointF rectTop;
    double rectWidth;
    double rectHeight;
    int startAngle;//起始角度
    int spanAngle;//旋转角度
};

/////////////////////////////////////Text//////////////////////////////
class HTextObj : public HBaseObj
{
public:
    HTextObj();
    virtual ~HTextObj();
    //xml文件读写
    virtual void readXml(QDomElement* data);
    virtual void writeXml(QDomElement* data);

    virtual QString TagName();
    //拷贝克隆
    virtual void copyTo(HBaseObj* obj);

    virtual DRAWSHAPE getShapeType();

public:
    void setTopLeftPoint(QPointF topLeft);
    QPointF getTopLeftPoint();

    void setRectWidth(double width);
    double getRectWidth();

    void setRectHeight(double height);
    double getRectHeight();


    void setTextColorName(QString strClrName);
    QString getTextColorName();

    void setLayout(ushort layout);
    ushort getLayout();

    void setHorizontalAlign(int hAlign);
    int getHorizontalAlign();

    void setVerticalAlign(int vAlign);
    int getVerticalAlign();

    void setTextFontName(QString strFontName);
    QString getTextFontName();

    void setPointSize(int ptSize);
    int getPointSize();

    void setWeight(int weight);
    int getWeigth();

    void setItalic(bool bitalic);
    bool getItalic();

    void setTextContent(QString strContent);
    QString getTextContent();


private:
    //矩形范围
    QPointF topLeft;
    //QPointF rectTop;
    double rectWidth;
    double rectHeight;

    QString strTextContent;//文字
    //文字颜色,文字字体,水平对齐，垂直对齐,布局方式
    ushort layout;
    int horizontalAlign;
    int verticalAlign;
    QString textColorName;
    QString textFontName;
    int pointSize;//字体大小
    int weight;//粗体
    bool italic;//斜体
};
#endif // HLINEOBJ_H
