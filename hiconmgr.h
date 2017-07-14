#ifndef HICONMGR_H
#define HICONMGR_H
#include "hiconscene.h"
#include "hiconframe.h"
#include "hicondocument.h"
#include "hiconstate.h"

class HIconFrame;
class HIconDocument;
class HIconState;
class HIconMgr
{
public:
    HIconMgr();
    HIconTemplate* getIconTemplate();
    HIconState* getIconState();
    HIconFrame* getIconFrame();

    void setBackgroundColor(QString clrName);
    QString getBackgroundColor();
    void setShowGrid(bool show);
    bool getShowGrid();
    void setShowCenterLine(bool show);
    bool getShowCenterLine();
public:
    void New(const QString& catalogName,const int& nIconType);
    void Del(const QString& catalogName,const int& nIconType,const QString& uuid);
    bool Save();
    void Open(const QString& catalogName,const int& nIconType,const QString& uuid);
private:
    bool bShowGrid;
    bool bShowCenterLine;
    QString strBgClr;
    HIconFrame* pIconFrame;
    HIconDocument* pIconDocument;
    HIconState* pIconState;
};

#endif // HICONMGR_H
