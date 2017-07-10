#ifndef HICONWIDGET_H
#define HICONWIDGET_H

#include <QWidget>

#include "iconapi.h"
class QTabBar;
class HIconFrame;
class HIconMgr;
class HIconWidget : public QWidget
{
    Q_OBJECT
public:
    HIconWidget(HIconMgr* iconMgr);
    void newIconWidget();

    void refreshIconWidget();


    QTabBar* getTabBar(){return pTabBar;}

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    //HIconFrame* getIconFrame(){return pIconFrame;}
public slots:
    void addShowPattern();
    void delShowPattern();
    void renameShowPattern();
    void patternChanged(int curPatternId);
private:
    HIconMgr* pIconMgr;
    QTabBar* pTabBar;
};

#endif // HICONWIDGET_H
