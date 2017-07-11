#ifndef HICONPREVIEW_H
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
public:
    void init();
protected:
    bool eventFilter(QObject *, QEvent *);
public slots:
    void refresh();

    void onDefaultSizeChanged();
    void onRefreshChanged();
    void drawIcon(QPainter* p);
private:
    Ui::IconPreview *ui;
    HIconMgr* pIconMgr;
    QRectF  pixRect;
    QPixmap pixMap;
};

#endif // HICONPREVIEW_H
