#ifndef HNEWICONDLG_H
#define HNEWICONDLG_H

#include <QDialog>

namespace Ui {
class NewIconDlg;
}

class HNewIconDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HNewIconDlg(QWidget *parent = 0);
    ~HNewIconDlg();
    void init();
    QString getIconName();
public slots:
    void okIconName();
    void noIconName();
private:
    Ui::NewIconDlg *ui;
    QString strIconName;
};

#endif // HNEWICONDLG_H
