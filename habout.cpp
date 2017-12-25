#include "habout.h"
#include "ui_about.h"
#include <QPainter>
HAbout::HAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HAbout)
{
    ui->setupUi(this);

}

HAbout::~HAbout()
{
    delete ui;
}

void HAbout::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage image;// = new QImage();
    image.load(":/images/about.png");
    painter.drawImage(100,8,image);
}
