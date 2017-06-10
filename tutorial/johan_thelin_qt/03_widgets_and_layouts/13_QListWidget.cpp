/*
  This sample uses 2 QListWidget(s) and 2 push buttons to move items from
  one list into the other and back.

  The list widget is used to present a list of items to the user.
  You can add widgets to the list using the addItem(const QString&) or
  addItems(const QStringList&) methods.
  When the user changes the current item, you can tell by connecting to the
  currentItemChanged(QListWidgetItem *, QListWidgetItem *) or
  currentTextChanged(const QString&) signals.

  With the selectionMode property, you can enable the user to select only one
  item, a contiguous range of items, or all items. Whenever the selection is
  changed, the itemSelectionChanged signal is emitted.


  Build:
  qmake -project -nopwd $PWD/13_QListWidget.h $PWD/13_QListWidget.cpp \
                 -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include "13_QListWidget.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;
    QGridLayout* layout = new QGridLayout(&dlg);

    QListWidget* leftList = new QListWidget();
    QListWidget* rightList = new QListWidget();
    QPushButton* leftBn = new QPushButton("<<");
    QPushButton* rightBn = new QPushButton(">>");

    layout->addWidget(leftList, 0, 0, 3, 1);
    layout->addWidget(rightList, 0, 2, 3, 1);
    layout->addWidget(leftBn, 0, 1);
    layout->addWidget(rightBn, 1, 1);

    QStringList items;
    items << "Argentine" << "Brazilian" << "South African" <<
             "USA West" << "Monaco" << "Belgian" << "Spanish" <<
             "Swedish" << "French" << "British" << "German" <<
             "Austrian" << "Dutch" << "Italian" << "USA East" <<
             "Canadian";
    leftList->addItems(items);

    Simple* simple = new Simple(&dlg);
    simple->leftList = leftList;
    simple->rightList = rightList;

    QObject::connect(leftBn,                // sender
                     SIGNAL(clicked()),     // signal
                     simple,                // receiver
                     SLOT(moveLeft()));     // slot

    QObject::connect(rightBn,               // sender
                     SIGNAL(clicked()),     // signal
                     simple,                // receiver
                     SLOT(moveRight()));    // slot

    dlg.show();
    return app.exec();
}


Simple::Simple(QObject *parent) : QObject(parent)
{
    leftList = NULL;
    rightList = NULL;
}

void Simple::moveLeft()
{
    if(leftList == NULL || rightList == NULL) return;

    if(rightList->selectedItems().count() != 1)
        return;

    QListWidgetItem* item = rightList->takeItem(rightList->currentRow());
    leftList->addItem(item);
}

void Simple::moveRight()
{
    if(leftList == NULL || rightList == NULL) return;

    if(leftList->selectedItems().count() != 1)
        return;

    QListWidgetItem* item = leftList->takeItem(leftList->currentRow());
    rightList->addItem(item);
}
