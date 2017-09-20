#ifndef HABOUT_H
#define HABOUT_H

#include <QDialog>

namespace Ui {
class HAbout;
}

class HAbout : public QDialog
{
    Q_OBJECT

public:
    explicit HAbout(QWidget *parent = 0);
    ~HAbout();
protected:
    virtual void	paintEvent(QPaintEvent * event);
private:
    Ui::HAbout *ui;
   // QImage *image;
};

#endif // HABOUT_H
