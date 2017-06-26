#include "hnewicondlg.h"
#include "ui_newicondlg.h"

HNewIconDlg::HNewIconDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewIconDlg)
{
    ui->setupUi(this);
    init();
}

HNewIconDlg::~HNewIconDlg()
{
    delete ui;
}

void HNewIconDlg::init()
{
    setWindowTitle(QStringLiteral("图元名称"));
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(okIconName()));
    connect(ui->noBtn,SIGNAL(clicked(bool)),this,SLOT(noIconName()));

}

void HNewIconDlg::okIconName()
{
    strIconName = ui->okBtn->text();
    QDialog::accept();
}

void HNewIconDlg::noIconName()
{
    QDialog::reject();
}

QString HNewIconDlg::getIconName()
{
    return strIconName;
}
