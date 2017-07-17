#ifndef HICONTYPE_H
#define HICONTYPE_H
/*
 主要是图元类型的一些信息

*/
#include <QObject>

class HIconType : public QObject
{
public:
    HIconType();

public:
   void setIconTypeName(const QString &strName);
   QString getIconTypeName();
   void setIconType(int type);
   int getIconType();
   void setParentType(int pType);
   int getParentType();
private:
    QString strIconTypeName; //开关、刀闸、遥测、接地牌....
    int nIconTypeId;//开关、刀闸等类型
    int nParentType; //遥信、遥测、接地牌等
};

#endif // HICONTYPE_H
