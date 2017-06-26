#include "hbaseobj.h"
#include <QVariant>

HBaseObj::HBaseObj(QObject *parent) : QObject(parent)
{
    init();
}

HBaseObj::~HBaseObj()
{
}

QString HBaseObj::TagName()
{
    return QString("基础");
}

void HBaseObj::init()
{
    strObjName = "baseobj"; //对象名称
    drawShape = enumNo;//图符类型(直线\圆)
    originX = 0;//原点位置（x,y)
    originY = 0;

    //线条方面
    strLineColor = "#00FF00";//线条颜色
    nLineWidth = 2;//线宽
    nLineStyle = (qint8)Qt::SolidLine;//线型
    nLineJoinStyle = (qint8)Qt::BevelJoin;//线连接处形状
    nLineCapStyle = (qint8)Qt::RoundCap;//线端形状


    //填充方面
    nFillWay = 0;//填充方式
    nFillStyle = (quint8)Qt::NoBrush;//填充风格
    strFillColor = "#00FF00"; //填充颜色
    nFillDirection = DIRECT_BOTTOM_TO_TOP;//填充方向
    nFillPercentage = 100;//填充比例

    //边框透明度
    bFrameSee = true;//边框可见
    nTransparency = 0; //透明度 0:不透明 100完全透明

    fRotateAngle = 0.0;//旋转角度
    bHorizonTurn = false;//水平翻转
    bVerticalTurn = false;//垂直翻转
    bVisible = true;//是否显示
    bDeleted = true;//是否删除
    nStackOrder = 0;

    //父图符
    m_pParent = NULL;

}

void HBaseObj::readXml(QDomElement* dom)
{
    if(!dom)
        return;
  /*  drawShape = (DRAWSHAPE)dom->attribute("ObjType").toUInt();
    strObjName = dom->attribute("ObjName");
    originX = dom->attribute("X").toDouble();
    originY = dom->attribute("Y").toDouble();
    fRotateAngle = dom->attribute("RotateAngle").toDouble();
    fLightRange = dom->attribute("LightRange").toDouble();
    nLineWidth = dom->attribute("LineWidth").toUInt();
    nLineStyle = dom->attribute("LineStyle").toUInt();
    nLineJoinStyle = dom->attribute("LineJoinStyle").toUInt();
    nLineCapStyle = dom->attribute("LineCapStyle").toUInt();
    bHorizonTurn = dom->attribute("HorizonTurn").toInt();
    bVerticalTurn = dom->attribute("VerticalTurn").toInt();
    bVisible = dom->attribute("Visible").toInt();
    bDeleted = dom->attribute("Delete").toInt();
    nStackOrder = dom->attribute("StackOrder").toInt();
    QString lc = dom->attribute("LineColor");
    if(!lc.isEmpty())
    {
        mLineColor = QColor(lc);
    }*/


}

void HBaseObj::writeXml(QDomElement* dom)
{
    if(!dom)
        return;
   /* dom->setTagName(TagName());
    dom->setAttribute("ObjType",drawShape);
    dom->setAttribute("ObjName",strObjName);
    dom->setAttribute("X",originX);
    dom->setAttribute("Y",originY);

    dom->setAttribute("RotateAngle",fRotateAngle);
    dom->setAttribute("LightRangle",fLightRange);
    dom->setAttribute("LineWidth",nLineWidth);
    dom->setAttribute("LineStyle",nLineStyle);
    dom->setAttribute("LineJoinStyle",nLineJoinStyle);
    dom->setAttribute("LineCapStyle",nLineCapStyle);
    dom->setAttribute("HorizonTurn",bHorizonTurn);
    dom->setAttribute("VerticalTurn",bVerticalTurn);

    dom->setAttribute("Visible",bVisible);
    dom->setAttribute("Delete",bDeleted);
    dom->setAttribute("StackOrder",nStackOrder);
    dom->setAttribute("LineColor",mLineColor.name());*/

}

//拷贝克隆
void HBaseObj::copyTo(HBaseObj* obj)
{
   /* obj->drawShape = drawShape;
    obj->strObjName = strObjName;
    obj->originX = originX;
    obj->originY = originY;
    obj->fRotateAngle = fRotateAngle;
    obj->fLightRange = fLightRange;
    obj->nLineWidth = nLineWidth;
    obj->nLineStyle = nLineStyle;
    obj->nLineJoinStyle = nLineJoinStyle;
    obj->nLineCapStyle = nLineCapStyle;
    obj->bHorizonTurn = bHorizonTurn;
    obj->bVerticalTurn = bVerticalTurn;
    obj->bVisible = bVisible;
    obj->bDeleted = bDeleted;
    obj->nStackOrder = nStackOrder;
    obj->setLineColor(&mLineColor);*/
}

//设置属性值 By Name
bool HBaseObj::setProperty(const QString &name, const QVariant &value)
{
    if("X" == name)
    {
        originX = value.toDouble();
    }
    else if("Y" == name)
    {
        originX = value.toDouble();
    }
    else if("Name" == name)
    {
        strObjName = value.toString();
    }
    else if("OBJID" == name)
    {
        nObjectId = value.toInt();
    }
    else if("RotateAngle" == name)
    {
        fRotateAngle = value.toDouble();
    }
    else if("LineWidth" == name)
    {
        nLineWidth = value.toInt();
    }
    else if("LineStyle" == name)
    {
        nLineStyle = value.toInt();
    }
    else if("LineJoinStyle" == name)
    {
        nLineJoinStyle = value.toInt();
    }
    else if("LineCapStyle" == name)
    {
        nLineCapStyle = value.toInt();
    }
    else if("LineColor" == name)
    {
        //QColor color = QColor(value.toString());
        //setLineColor(&color);
    }

    return true;
}

QVariant HBaseObj::getProperty(const QString &name)
{
    QVariant val;
    if("X" == name)
    {
        val = QVariant(originX);
    }
    else if("Y" == name)
    {
        val = QVariant(originY);
    }
    else if("Name" == name)
    {
        val = QVariant(strObjName);
    }
    else if("RotateAngle" == name)
    {
        val = QVariant(fRotateAngle);
    }
    else if("LineWidth" == name)
    {
        val = QVariant(nLineWidth);
    }
    else if("LineStyle" == name)
    {
        val = QVariant(nLineStyle);
    }
    else if("LineJoinStyle" == name)
    {
        val = QVariant(nLineJoinStyle);
    }
    else if("LineCapStyle" == name)
    {
        val = QVariant(nLineCapStyle);
    }
    else if("LineColor" == name)
    {
        val = QVariant(strLineColor);
    }
    else if("FrameSee" == name)
    {
        val = QVariant(bFrameSee);
    }
    else if("FillWay" == name)
    {
        val = QVariant(nFillWay);
    }
    else if("FillStyle" == name)
    {
        val = QVariant(nFillStyle);
    }
    else if("FillColor" == name)
    {
        val = QVariant(strFillColor);
    }
    else if("FillDirection" == name)
    {
        val = QVariant(nFillDirection);
    }
    else if("FillPercentage" == name)
    {
        val = QVariant(nFillPercentage);
    }
    else if("Transparency" == name)
    {
        val = QVariant(nTransparency); //透明度
    }
    return val;
}

//设置属性值 By ID
bool HBaseObj::setPropertyValue(int nId,const QVariant &value)
{
    return false;
}

QVariant HBaseObj::getPropertyValue(int nId)
{
    return false;
}

int HBaseObj::getObjID()
{
    return nObjectId;
}

void HBaseObj::setObjID(int nObjID)
{
    nObjectId = nObjID;
}

void HBaseObj::setOX(double x)
{
    originX = x;
}

void HBaseObj::setOY(double y)
{
    originY = y;
}

//形状类型
DRAWSHAPE HBaseObj::getShapeType()
{
    return drawShape;
}

void HBaseObj::setShapeType(DRAWSHAPE t)
{
    drawShape = t;
}

//线条颜色
void HBaseObj::setLineColorName(QString clrName)
{
    strLineColor = clrName;
}

QString HBaseObj::getLineColorName()
{
   return strLineColor;
}

//线宽
void HBaseObj::setLineWidth(quint8 lineWidth)
{
    nLineWidth = lineWidth;
}

quint8 HBaseObj::getLineWidth()
{
    return nLineWidth;
}

void HBaseObj::setLineStyle(Qt::PenStyle style)
{
    nLineStyle = style;
}

Qt::PenStyle HBaseObj::getLineStyle()
{
    return (Qt::PenStyle)nLineStyle;
}

//线连接处形状
void HBaseObj::setLineJoinStyle(Qt::PenJoinStyle style)
{
    nLineJoinStyle = style;
}

Qt::PenJoinStyle HBaseObj::getLineJoinStyle()
{
    return (Qt::PenJoinStyle)nLineJoinStyle;
}

//线端形状
void HBaseObj::setLineCapStyle(Qt::PenCapStyle style)
{
    nLineCapStyle = style;
}

Qt::PenCapStyle HBaseObj::getLineCapStyle()
{
    return (Qt::PenCapStyle)nLineCapStyle;
}

//填充方式
void HBaseObj::setFillWay(quint8 fillWay)
{
    nFillWay = fillWay;
}

quint8 HBaseObj::getFillWay()
{
    return nFillWay;
}

//填充风格
void HBaseObj::setFillStyle(Qt::BrushStyle style)
{
    nFillStyle = style;
}

Qt::BrushStyle HBaseObj::getFillStyle()
{
    return (Qt::BrushStyle)nFillStyle;
}

//填充方向
void HBaseObj::setFillDirection(quint8 fillDirection)
{
    nFillDirection = fillDirection;
}

quint8 HBaseObj::getFillDirection()
{
    return nFillDirection;
}

//填充比例
void HBaseObj::setFillPercentage(quint8 fillPer)
{
    nFillPercentage = fillPer;
}

quint8 HBaseObj::getFillPercentage()
{
    return nFillPercentage;
}

//边框可见
void HBaseObj::setFrameSee(bool frameSee)
{
    bFrameSee = frameSee;
}

bool HBaseObj::getFrameSee()
{
    return bFrameSee;
}

//透明度
void HBaseObj::setTransparency(quint8 transparency)
{
    nTransparency = transparency;
}

quint8 HBaseObj::getTransparency()
{
    return nTransparency;
}


//填充色
void HBaseObj::setFillColorName(QString clrName)
{
    strFillColor = clrName;
}

QString HBaseObj::getFillColorName()
{
    return strFillColor;
}

//边框色
void HBaseObj::setBorderColor(const QColor* c)
{

}

QColor HBaseObj::getBorderColor()
{
    return QColor();
}

//文字色
void HBaseObj::setTextColor(const QColor* c)
{

}

QColor HBaseObj::getTextColor()
{
    return QColor();
}

//是否旋转
bool HBaseObj::isRotated(qint8 nFlag)
{
    return false;
}

//旋转角度
void HBaseObj::setRotateAngle()
{

}

float HBaseObj::getRotateAngle()
{
    return 0;
}

//增加一个角度
void HBaseObj::setRotateAdd(float fAngle)
{

}

//翻转
bool HBaseObj::isTurned(qint8 nFlag)
{
    return false;
}

//是否水平翻转
bool HBaseObj::isTurn(bool bHorizonTurn)
{
    return false;
}

//设置翻转
void HBaseObj::setTurn(bool bHorizon,bool bVertical)
{

}

//是否可见
void HBaseObj::setVisible(qint8 vis,int nFlag)
{

}

qint8 HBaseObj::isVisible()
{
    return bVisible;
}

//是否删除
void HBaseObj::setDeleted(bool bDel)
{

}

bool HBaseObj::isDeleted()
{
    return bDeleted;
}

//叠放次序
qint64 HBaseObj::getStackOrder()
{
    return nStackOrder;
}

void HBaseObj::setStackOrder(qint64 nStack)
{

}

