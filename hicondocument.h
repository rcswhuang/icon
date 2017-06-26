#ifndef HICONDOCUMENT_H
#define HICONDOCUMENT_H

#include <QObject>
#include "hicontype.h"
#include "iconapi.h"
#include "hicontemplate.h"
#include "hiconmgr.h"
class HIconMgr;
class HIconDocument : public QObject
{
public:
    HIconDocument(HIconMgr* iconMgr);
public:
    void loadTemplateFile();//加载所有的模板文件
    void initIconType();

public:
    void New(const QString& strTemplateName,int nTemplateType);
    void Del(const QString& strTemplateName,int nTemplateType,const QString& strUuid);
    HIconTemplate* getCurrentTemplate();
    HIconTemplate* findIconTemplateByTypeAndUuid(int nTemplateType,const QString& strUuid);
public:
    QList<HIconType*> pIconTypeList;
    HIconTemplate* pCurIconTemplate;
    HIconMgr* pIconMgr;
    QList<HIconTemplate*> pIconTemplateList;
};

#endif // HICONDOCUMENT_H
