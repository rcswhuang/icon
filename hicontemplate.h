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

    void setCatalogName(QString name);
    QString getCatalogName();

    void setCatalogType(int type);
    int getCatalogType();

    void setDefaultSize(const QSizeF& size);
    QSizeF getDefaultSize();

    QUuid& getUuid();
    void setUuid(const QUuid &id);

    HIconSymbol* getSymbol();

    void clear();

    void setModify(bool modify);
    bool getModify();

private:
    int nVersion;
    QString strCatalogName;//图元目录名称 遥测 遥信等
    int nCatalogType;//图元目录类型 遥测 遥信等
    QSizeF sDefaultSize;
    QUuid uUid;
    HIconSymbol* pIconSymbol;
};

#endif // HICONDOCUMENT_H
