#ifndef HICONMGR_H
#define HICONMGR_H
#include "hiconscene.h"
#include "hiconframe.h"
#include "hicondocument.h"
#include "hiconstate.h"
#include <QUndoStack>
class HIconFrame;
class HIconDocument;
class HIconState;
class HIconMgr
{
public:
    HIconMgr();
    HIconDocument* getIconDocument();
    HIconTemplate* getIconTemplate();
    HIconState* getIconState();
    HIconFrame* getIconFrame();
    QUndoStack* getIconUndoStack();

    void setBackgroundColor(QString clrName);
    QString getBackgroundColor();
    void setShowGrid(bool show);
    bool getShowGrid();
    void setShowCenterLine(bool show);
    bool getShowCenterLine();
public:
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    bool Save(bool savefile=false);
private:
    bool bShowGrid;
    bool bShowCenterLine;
    QString strBgClr;
    HIconFrame* pIconFrame;
    HIconDocument* pIconDocument;
    HIconState* pIconState;
    QUndoStack* pIconUndoStack;
};

#endif // HICONMGR_H
