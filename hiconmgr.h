﻿#ifndef HICONMGR_H
#define HICONMGR_H
#include "hiconscene.h"
#include "hiconframe.h"
#include "hicondocument.h"
#include "hiconstate.h"
#include "hiconop.h"
#include <QUndoStack>
class HIconFrame;
class HIconDocument;
class HIconState;
class HIconOp;
class HIconMgr
{
public:
    HIconMgr();
    HIconDocument* getIconDocument();
    HIconTemplate* getIconTemplate();
    HIconFrame* getIconFrame();
    QUndoStack* getIconUndoStack();
    HIconOp* getIconOp();

    void setBackgroundColor(QString clrName);
    QString getBackgroundColor();
    void setShowGrid(bool show);
    bool getShowGrid();
    void setShowCenterLine(bool show);
    bool getShowCenterLine();

    void setDrawShape(DRAWSHAPE ds);
    DRAWSHAPE getDrawShape();
    void setSelectMode(SELECTMODE ds);
    SELECTMODE getSelectMode();

public:
    void New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType);
    void Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    void Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid);
    bool Save(bool savefile=false);
private:
    DRAWSHAPE m_drawShape;
    SELECTMODE m_selectMode;
    bool m_bShowGrid;
    bool m_bShowCenterLine;
    QString m_strBgClr;
    HIconFrame* m_pIconFrame;
    HIconDocument* m_pIconDocument;
    HIconState* m_pIconState;
    HIconOp* m_pIconOp;
    QUndoStack* m_pIconUndoStack;
};

#endif // HICONMGR_H
