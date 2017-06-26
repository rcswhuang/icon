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
    HIconTemplate(QObject* parent = 0);
    ~HIconTemplate();
public:
    void readXml(const QString &strXmlFile);
    void writeXml(const QString &strXmlFile);
    void readXml(QDomElement* dom);
    void writeXml(QDomElement *dom);

    void setVersion(int version);
    int getVersion();

    void setAttrName(QString name);
    QString getAttrName();

    void setIconType(int type);
    int getIconType();

    void setDefaultSize(const QSizeF& size);
    QSizeF getDefaultSize();

    QUuid& getUuid();
    void setUuid(const QUuid &id);

    HIconSymbol* getSymbol();

public:

private:
    int nVersion;
    QString strAttrName;//图元属性名称 遥测 遥信等
    int nIconType;//图元类型 遥测 遥信等
    QSizeF sDefaultSize;
    QUuid uUid;
    HIconSymbol* pIconSymbol;
};

#endif // HICONDOCUMENT_H
