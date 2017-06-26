#ifndef HELLIPSEOBJ_H
#define HELLIPSEOBJ_H
#include "hbaseobj.h"

class HEllipseObj : public HBaseObj
{
public:
    HEllipseObj();
    ~HEllipseObj();
protected:
    void drawEllipse(QPainter* painter,int nWidth,uint uZoomRate);
public:
    void draw(QPainter* painter,int nDrawMode,uint uZoomRate);
    void inWhichArea(QPoint point,uint uZoomRate);
    void pointInBorder(QPoint point,uint uZoomRate);


    void sortCoord();

};

#endif // HELECLINEOBJ_H
