#include "hicontemplate.h"
#include <QFile>
#include <QTextStream>
HIconTemplate::HIconTemplate(QObject* parent)
{
    if(uUid.isNull())
    {
        uUid = QUuid::createUuid();
    }
    pIconSymbol = new HIconSymbol;
    sDefaultSize = QSizeF(50,50);
    nIconTypeId = 0;
    nVersion = 1;
}

HIconTemplate::~HIconTemplate()
{
    if(pIconSymbol)
    {
        delete pIconSymbol;
        pIconSymbol = NULL;
    }
}


void HIconTemplate::readXml(const QString &strXmlFile)
{
    QFile file(strXmlFile);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream dsm(&file);
    QDomDocument doc;
    doc.setContent(dsm.readAll());
    QDomElement root = doc.documentElement();
    if(root.isNull())
        return;
    readXml(&root);
    file.close();
}

void HIconTemplate::writeXml(const QString &strXmlFile)
{
    QFile file(strXmlFile);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QDomDocument doc;
    QDomElement root = doc.createElement("IconTemplate");
    if(root.isNull())
        return;
    doc.appendChild(root);
    writeXml(&root);
    QDataStream dsm(&file);
    dsm<<doc.toString();
    file.close();
}

void HIconTemplate::readXml(QDomElement* dom)
{
    if(!dom)
        return;

    strIconTypeName = dom->attribute("AttrName");
    nIconTypeId = dom->attribute("AttrType").toInt();
    uUid = QUuid(dom->attribute("UUID"));
    double w = dom->attribute("DefaultWidth").toDouble();
    double h = dom->attribute("DefaultHeight").toDouble();
    sDefaultSize = QSizeF(w,h);
    QDomElement symbolDom = dom->namedItem(strIconTypeName).toElement();
    if(!symbolDom.isNull())
    {
        pIconSymbol->readXml(&symbolDom);
    }
}

void HIconTemplate::writeXml(QDomElement *dom)
{
    if(!dom)
        return;

    dom->setAttribute("TypeName",strIconTypeName);
    dom->setAttribute("AttrType",nIconTypeId);
    dom->setAttribute("UUID",uUid.toString());
    dom->setAttribute("DefaultWidth",sDefaultSize.width());
    dom->setAttribute("DefaultHeight",sDefaultSize.height());

    QDomElement symbolDom = dom->ownerDocument().createElement("IconSymbol");
    dom->appendChild(symbolDom);
    if(pIconSymbol)
    {
        pIconSymbol->writeXml(&symbolDom);
    }
}

void HIconTemplate::setVersion(int version)
{
    nVersion = version;
}

int HIconTemplate::getVersion()
{
    return nVersion;
}

void HIconTemplate::setIconTypeName(QString name)
{
    strIconTypeName = name;
}

QString HIconTemplate::getIconTypeName()
{
    return strIconTypeName;
}

void HIconTemplate::setIconTypeId(int type)
{
    nIconTypeId = type;
}

int HIconTemplate::getIconTypeId()
{
    return nIconTypeId;
}

void HIconTemplate::setDefaultSize(const QSizeF& size)
{
    sDefaultSize = size;
}

QSizeF HIconTemplate::getDefaultSize()
{
    return sDefaultSize;
}

QUuid& HIconTemplate::getUuid()
{
    return uUid;
}

void HIconTemplate::setUuid(const QUuid &id)
{
    uUid = id;
}

HIconSymbol* HIconTemplate::getSymbol()
{
    if(pIconSymbol)
        return pIconSymbol;
    return NULL;
}



