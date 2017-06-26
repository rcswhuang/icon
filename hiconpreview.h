﻿#ifndef HICONPREVIEW_H
#define HICONPREVIEW_H

#include <QDialog>
#include "hiconmgr.h"
namespace Ui {
class IconPreview;
}

class HIconPreview : public QDialog
{
    Q_OBJECT

public:
    explicit HIconPreview(HIconMgr* iconMgr,QWidget *parent = 0);
    ~HIconPreview();

protected:
    bool eventFilter(QObject *, QEvent *);
public slots:
    void refresh();

    void onDefaultSizeChanged();
    void onRaditChanged();
    void drawIcon(QPainter* p);
private:
    Ui::IconPreview *ui;
    HIconMgr* pIconMgr;
    QRectF  pixRect;
    QPixmap pixMap;
};

#endif // HICONPREVIEW_H
