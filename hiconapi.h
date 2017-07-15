#ifndef ICONAPI_H
#define ICONAPI_H


//图元类型
#define TEMPLATE_TYPE_NULL 0x00
#define TEMPLATE_TYPE_DIGITAL 0x01
#define TEMPLATE_TYPE_ANALGOUE 0x02
#define TEMPLATE_TYPE_YK 0x03
#define TEMPLATE_TYPE_PLUSE 0x04
#define TEMPLATE_TYPE_TAP 0x05
#define TEMPLATE_TYPE_LIGHT 0x06
#define TEMPLATE_TYPE_JDPAI 0x07
#define TEMPLATE_TYPE_MAX 0x08

//具体某一个图元
#define TEMPLATE_TYPE_CHILD 0x20

#define ICON_TYPE_STATE 0x05
#define ICON_TYPE_VALUE 0x06


//定义设备类型元素
#define DEVICE_TYPE_ICONSYMBOL 500

//定义icon的元素的类型
#define OBJ_TYPE_NULL 1000
#define OBJ_TYPE_LINE 1001  //直线
#define OBJ_TYPE_RECTANGLE 1002 //矩形
#define OBJ_TYPE_SOLID_RECTANGLE 1003 //实矩形
#define OBJ_TYPE_ELLIPSE 1004 //椭圆
#define OBJ_TYPE_SOLID_ELLIPSE 1005 //实椭圆
#define OBJ_TYPE_ARC  1006//弧
#define OBJ_TYPE_PIE   1007//饼型


//定义绘制icon工具的类型
#define TOOL_TYPE_NULL  0
#define TOOL_TYPE_LINE  1
#define TOOL_TYPE_RECTANGLE 2
#define TOOL_TYPE_SOLID_RECT 3
#define TOOL_TYPE_ELLIPSE 4
#define TOOL_TYPE_SOLID_ELLIPSE 5
#define TOOL_TYPE_ARC 6
#define TOOL_TYPE_PIE 7


//定义绘制编辑状态
#define SELECTING_STATE 0x100
#define RESELECT_STATE 0x101
#define CREATE_STATE 0x102


#define LEFTMARGIN 10
#define TOPMARGIN 10
#define SYMBOLWIDTH 200
#define SYMBOLHEIGHT 200
#define BROWERWIDTH 100
#define BROWERHEIGHT 100

#define PI 3.14

enum DRAWSHAPE
{
    enumSelection, //选择模式
    enumMulSelection,
    enumConnect, //连接模式

    //绘制对象
    enumNo,
    enumLine,
    enumRectangle,
    enumEllipse,
    enumArc,
    enumPolygon,
    enumCircle,
    enumPie,
    enumText
};

//选择状态
enum SELECTMODE
{
    enumNone,
    enumSelect, //选择对象
    enumMove,   //移动对象
    enumSize   //改变对象
};

//填充方向
#define DIRECT_NULL          0x00 //无方向
#define DIRECT_BOTTOM_TO_TOP 100 //由底到顶
#define DIRECT_TOP_TO_BOTTOM 101 //有顶到底
#define DIRECT_LEFT_TO_RIGHT 102 //由左到右
#define DIRECT_RIGHT_TO_LEFT 103 //由左到右
#define DIRECT_VER_TO_OUT    104 //垂直到外
#define DIRECT_HORi_TO_OUT   105 //水平向外
#define DIRECT_VER_TO_IN     106 //垂直向里
#define DIRECT_HORI_TO_IN    107 //垂直向里


//文字布局
#define LAYOUT_TEXT_NULL 00
#define LAYOUT_TEXT_FULL 01
#define LAYOUT_TEXT_VERTICAL 02
#define LAYOUT_TEXT_HORIZON 03











#endif // ICONAPI_H
