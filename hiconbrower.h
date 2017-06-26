#ifndef HICONBROWER_H
#define HICONBROWER_H
#include <QWidget>
#include <QString>
class HIconTreeWidget;
/*
 * 浏览单元
*/

class HIconViewFrame : public QWidget
{
public:
    HIconViewFrame(QWidget* parent = 0);
    ~HIconViewFrame();

};


class HIconBrower : public QWidget
{
    Q_OBJECT
public:
    HIconBrower(QWidget* parent = 0);

public:
    void init();
    void newIcon(const QString& strName,const int& nIconType);
signals:
    void IconNew(const QString& strName,const int& nIconType);
public slots:

public:
    HIconTreeWidget* pIconTreeWidget;
};

#endif // HICONBROWER_H
