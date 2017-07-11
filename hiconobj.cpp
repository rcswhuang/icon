﻿#include "hiconobj.h"
#include "hiconlineitem.h"
#include <QVariant>
HLineObj::HLineObj()
{
    arrowHeight = 0;
    arrowWidth = 0;
    arrowStart = 0;
    arrowEnd = 0;
}

HLineObj::~HLineObj()
{
  // pLineItem = NULL;
}

void HLineObj::readXml(QDomElement* data)
{

}

void HLineObj::writeXml(QDomElement* data)
{

}

QString HLineObj::TagName()
{
    return "Line";
}

//拷贝克隆
void HLineObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}

//设置属性值 By Name
bool HLineObj::setProperty(const QString &name, const QVariant &value)
{
    bool bResult = HBaseObj::setProperty(name,value);
    return bResult;
}

QVariant HLineObj::getProperty(const QString &name)
{
    QVariant val = HBaseObj::getProperty(name);
    return val;
}

//设置属性值 By ID
bool HLineObj::setPropertyValue(int nId,const QVariant &value)
{
    return false;
}

QVariant HLineObj::getPropertyValue(int nId)
{
    return QVariant();
}


DRAWSHAPE HLineObj::getShapeType()
{
    return enumLine;
}


void HLineObj::setArrowStart(quint8 start)
{
    arrowStart = start;
}

quint8 HLineObj::getArrowStart()
{
    return arrowStart;
}

void HLineObj::setArrowEnd(quint8 end)
{
    arrowEnd = end;
}

quint8 HLineObj::getArrowEnd()
{
    return arrowEnd;
}

void HLineObj::setArrowWidth(quint16 width)
{
    arrowWidth = width;
}

quint16 HLineObj::getArrowWidth()
{
    return arrowWidth;
}

void HLineObj::setArrowHeight(quint16 height)
{
    arrowHeight = height;
}

quint16 HLineObj::getArrowHeight()
{
    return arrowHeight;
}
/////////////////////////////////////HRectObj//////////////////////////////////////
HRectObj::HRectObj()
{
    rectHeight = 0;
    rectWidth = 0;
}

HRectObj::~HRectObj()
{

}

void HRectObj::readXml(QDomElement* data)
{

}

void HRectObj::writeXml(QDomElement* data)
{

}

QString HRectObj::TagName()
{
    return "Rectangle";
}

//拷贝克隆
void HRectObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}

//设置属性值 By Name
bool HRectObj::setProperty(const QString &name, const QVariant &value)
{
    bool bResult = HBaseObj::setProperty(name,value);
    return bResult;
}

QVariant HRectObj::getProperty(const QString &name)
{
    QVariant val = HBaseObj::getProperty(name);
    return val;
}

//设置属性值 By ID
bool HRectObj::setPropertyValue(int nId,const QVariant &value)
{
    return false;
}

QVariant HRectObj::getPropertyValue(int nId)
{
    return QVariant();
}


DRAWSHAPE HRectObj::getShapeType()
{
    return enumRectangle;
}


///////////////////////////////////HEllipseObj//////////////////////////////////////////////////
HEllipseObj::HEllipseObj()
{
    rectHeight = 0;
    rectWidth = 0;
}

HEllipseObj::~HEllipseObj()
{

}

void HEllipseObj::readXml(QDomElement* data)
{

}

void HEllipseObj::writeXml(QDomElement* data)
{

}

QString HEllipseObj::TagName()
{
    return "Ellipse";
}

//拷贝克隆
void HEllipseObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}

//设置属性值 By Name
bool HEllipseObj::setProperty(const QString &name, const QVariant &value)
{
    bool bResult = HBaseObj::setProperty(name,value);
    return bResult;
}

QVariant HEllipseObj::getProperty(const QString &name)
{
    QVariant val = HBaseObj::getProperty(name);
    return val;
}

//设置属性值 By ID
bool HEllipseObj::setPropertyValue(int nId,const QVariant &value)
{
    return false;
}

QVariant HEllipseObj::getPropertyValue(int nId)
{
    return QVariant();
}


DRAWSHAPE HEllipseObj::getShapeType()
{
    return enumEllipse;
}

///////////////////////////////////////////////HPolygonObj//////////////////////////////////////
HPolygonObj::HPolygonObj()
{
    pylist.clear();
}

HPolygonObj::~HPolygonObj()
{

}

void HPolygonObj::readXml(QDomElement* data)
{

}

void HPolygonObj::writeXml(QDomElement* data)
{

}

QString HPolygonObj::TagName()
{
    return "Polygon";
}

//拷贝克隆
void HPolygonObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}

//设置属性值 By Name
bool HPolygonObj::setProperty(const QString &name, const QVariant &value)
{
    bool bResult = HBaseObj::setProperty(name,value);
    return bResult;
}

QVariant HPolygonObj::getProperty(const QString &name)
{
    QVariant val = HBaseObj::getProperty(name);
    return val;
}

//设置属性值 By ID
bool HPolygonObj::setPropertyValue(int nId,const QVariant &value)
{
    return false;
}

QVariant HPolygonObj::getPropertyValue(int nId)
{
    return QVariant();
}


DRAWSHAPE HPolygonObj::getShapeType()
{
    return enumPolygon;
}



///////////////////////////////////////////////HArcObj//////////////////////////////////////
HArcObj::HArcObj()
{
    startAngle = 30;
    spanAngle = 240;
    bCloseCheck = false;
}

HArcObj::~HArcObj()
{

}

void HArcObj::readXml(QDomElement* data)
{

}

void HArcObj::writeXml(QDomElement* data)
{

}

QString HArcObj::TagName()
{
    return "Arc";
}

//拷贝克隆
void HArcObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}


DRAWSHAPE HArcObj::getShapeType()
{
    return enumArc;
}

void HArcObj::setStartAngle(int sAngle)
{
    startAngle = sAngle;
}

int HArcObj::getStartAngle()
{
    return startAngle;
}

void HArcObj::setSpanAngle(int spanangle)
{
    spanAngle = spanangle;
}

int HArcObj::getSpanAngle()
{
    return spanAngle;
}

void HArcObj::setCloseStatus(bool bcheck)
{
    bCloseCheck = bcheck;
}

bool HArcObj::getCloseStatus()
{
    return bCloseCheck;
}


///////////////////////////////////////////////HPieObj//////////////////////////////////////
HPieObj::HPieObj()
{
    startAngle = 30;
    spanAngle = 240;
}

HPieObj::~HPieObj()
{

}

void HPieObj::readXml(QDomElement* data)
{

}

void HPieObj::writeXml(QDomElement* data)
{

}

QString HPieObj::TagName()
{
    return "Pie";
}

//拷贝克隆
void HPieObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}


DRAWSHAPE HPieObj::getShapeType()
{
    return enumPie;
}

void HPieObj::setStartAngle(int sAngle)
{
    startAngle = sAngle;
}

int HPieObj::getStartAngle()
{
    return startAngle;
}

void HPieObj::setSpanAngle(int spanangle)
{
    spanAngle = spanangle;
}

int HPieObj::getSpanAngle()
{
    return spanAngle;
}


///////////////////////////////////////////////////////////////////////
HTextObj::HTextObj()
{
    strTextContent = "icon text";

    textColorName = "#00FF00";//线条颜色
    textFontName = QStringLiteral("微软雅黑");
    layout = LAYOUT_TEXT_NULL;
    horizontalAlign = Qt::AlignHCenter;
    verticalAlign = Qt::AlignVCenter;
    pointSize = 10;//字体大小
    weight = QFont::Normal;//粗体
    italic = false;//斜体
}

HTextObj::~HTextObj()
{

}

//xml文件读写
void HTextObj::readXml(QDomElement* data)
{

}

void HTextObj::writeXml(QDomElement* data)
{

}

QString HTextObj::TagName()
{
    return "Text";
}

//拷贝克隆
void HTextObj::copyTo(HBaseObj* obj)
{
    HBaseObj::copyTo(obj);
}

DRAWSHAPE HTextObj::getShapeType()
{
    return enumText;
}

void HTextObj::setTextColorName(QString strClrName)
{
    textColorName = strClrName;
}

QString HTextObj::getTextColorName()
{
    return textColorName;
}

void HTextObj::setLayout(ushort layout)
{
    this->layout = layout;
}

ushort HTextObj::getLayout()
{
    return layout;
}

void HTextObj::setHorizontalAlign(int hAlign)
{
    horizontalAlign = hAlign;
}

int HTextObj::getHorizontalAlign()
{
    return horizontalAlign;
}

void HTextObj::setVerticalAlign(int vAlign)
{
    verticalAlign = vAlign;
}

int HTextObj::getVerticalAlign()
{
    return verticalAlign;
}

void HTextObj::setTextFontName(QString strFontName)
{
    textFontName = strFontName;
}

QString HTextObj::getTextFontName()
{
    return textFontName;
}

void HTextObj::setPointSize(int ptSize)
{
    pointSize = ptSize;
}

int HTextObj::getPointSize()
{
    return pointSize;
}

void HTextObj::setWeight(int weight)
{
    this->weight = weight;
}

int HTextObj::getWeigth()
{
    return weight;
}

void HTextObj::setItalic(bool bitalic)
{
    italic = bitalic;
}

bool HTextObj::getItalic()
{
    return italic;
}

void HTextObj::setTextContent(QString strContent)
{
    strTextContent = strContent;
}

QString HTextObj::getTextContent()
{
    return strTextContent;
}


void HTextObj::setTopLeftPoint(QPointF topLeft)
{
    this->topLeft = topLeft;
}

QPointF HTextObj::getTopLeftPoint()
{
    return topLeft;
}

void HTextObj::setRectWidth(double width)
{
    rectWidth = width;
}

double HTextObj::getRectWidth()
{
    return rectWidth;
}

void HTextObj::setRectHeight(double height)
{
    rectHeight = height;
}

double HTextObj::getRectHeight()
{
    return rectHeight;
}

