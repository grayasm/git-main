#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}

const QString EditDialog::name() const
{
    return ui->nameEdit->text().replace("--", "").trimmed();
}
void EditDialog::setName(const QString& name)
{
    ui->nameEdit->setText(name);
}

const QString EditDialog::number() const
{
    return ui->numberEdit->text().replace("--", "").trimmed();
}

void EditDialog::setNumber(const QString& number)
{
    ui->numberEdit->setText(number);
}
