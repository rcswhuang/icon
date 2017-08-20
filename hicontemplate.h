#ifndef HICONTEMPLATE_H
#define HICONTEMPLATE_H

#include <QObject>
#include <QUuid>
#include <QtXml/QDomElement>
#include <QSizeF>
#include "hiconsymbol.h"
//存放ICON图元显示单元信息
class HIconTemplate : public QObject
{
public:
    HIconTemplate(const QUuid& uuid,QObject* parent = 0);
    ~HIconTemplate();
public:
    void readXml(const QString &strXmlFile);
    void writeXml(const QString &strXmlFile);
    void readXml(QDomElement* dom);
    void writeXml(QDomElement *dom);

    void copyTo(HIconTemplate *temp);

    void setVersion(int version);
    int getVersion();

    void setIconTypeName(QString name);
    QString getIconTypeName();

    void setIconTypeId(int type);
    int getIconTypeId();

    void setDefaultSize(const QSizeF& size);
    QSizeF getDefaultSize();

    QUuid& getUuid();
    void setUuid(const QUuid &id);

    HIconSymbol* getSymbol();

private:
    int nVersion;
    QString strIconTypeName;//图元属性名称 遥测 遥信等
    int nIconTypeId;//图元类型 遥测 遥信等
    QSizeF sDefaultSize;
    QUuid uUid;
    HIconSymbol* pIconSymbol;
};

#endif // HICONDOCUMENT_H
