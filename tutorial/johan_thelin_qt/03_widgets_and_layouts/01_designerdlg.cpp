#include "01_designerdlg.h"
#include "ui_01_designerdlg.h"

DesignerDlg::DesignerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DesignerDlg)
{
    ui->setupUi(this);
}

DesignerDlg::~DesignerDlg()
{
    delete ui;
}
