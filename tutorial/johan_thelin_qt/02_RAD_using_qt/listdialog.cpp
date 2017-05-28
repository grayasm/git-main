#include "listdialog.h"
#include "ui_listdialog.h"
#include "editdialog.h"

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog)
{
    ui->setupUi(this);

    // manual editing begin -->
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editItem()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    // <-- end
}

ListDialog::~ListDialog()
{
    delete ui;
}


// manual editing begin -->
void ListDialog::addItem()
{
    EditDialog dlg(this);

    if(dlg.exec() == QDialog::Accepted)
        ui->list->addItem(dlg.name() + " -- " + dlg.number());
}

void ListDialog::editItem()
{
    if(!ui->list->currentItem())
        return;

    QStringList parts = ui->list->currentItem()->text().split("--");

    EditDialog dlg(this);
    dlg.setName(parts[0].trimmed());
    dlg.setNumber(parts[1].trimmed());

    if(dlg.exec() == QDialog::Accepted)
        ui->list->currentItem()->setText(dlg.name() + " -- " + dlg.number());
}

void ListDialog::deleteItem()
{
    qDeleteAll(ui->list->selectedItems());
}
// <-- end
