#ifndef HICONDOCUMENT_H
#define HICONDOCUMENT_H

#include <QObject>
#include "hicontype.h"
#include "hiconapi.h"
#include "hicontemplate.h"
#include "hiconmgr.h"
class HIconMgr;
class HIconDocument : public QObject
{
public:
    HIconDocument(HIconMgr* iconMgr);
    ~HIconDocument();
public:

    void loadIconDoucument();
    void loadIconTemplateFile(QString strIconsPath);//加载所有的模板文件
    void saveIconDoucument();
    void saveIconTemplateFile(const QString& strIconsPath,const QString& strFolderName);//保存所有的模板文件
    void initIconType();

    //通过图元类型来获得存储的文件夹类型
    bool IsIconInFolder(const QString& strFolderName,const quint8& nIconType);

public:
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    bool Save();
    HIconTemplate* getCurrentTemplate();
    HIconTemplate* findIconTemplateByTypeAndUuid(int nTemplateType,const QString& strUuid);
    HIconTemplate* findIconTemplateByTemplateName(const QString& strTemplateName);
public:
    QList<HIconType*> pIconTypeList;
    HIconTemplate* pCurIconTemplate;
    HIconMgr* pIconMgr;
    QList<HIconTemplate*> pIconTemplateList;
};

#endif // HICONDOCUMENT_H
