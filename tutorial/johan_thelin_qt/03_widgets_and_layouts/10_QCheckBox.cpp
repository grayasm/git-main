/*
  A QCheckBox sample with 3 states: 0, 1 and 2
  The slot has the sample prototype with QCheckBox signal:
  void QCheckBox::stateChanged(int);


  Build:
  qmake -project -nopwd $PWD/10_QCheckBox.h     \
                        $PWD/10_QCheckBox.cpp   \
                        -o 10_QCheckBox.pro
  qmake -makefile -o Makefile "QT+=widgets" 10_QCheckBox.pro
  make
  ./10_QCheckBox
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include "10_QCheckBox.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;
    QVBoxLayout* layout = new QVBoxLayout(&dlg);

    QLabel* label = new QLabel();
    QCheckBox* checkbox = new QCheckBox("Testing");
    checkbox->setTristate(true);

    layout->addWidget(checkbox);
    layout->addWidget(label);

    Simple* simple = new Simple(&dlg);
    simple->label = label;

    QObject::connect(checkbox,                      // sender
                     SIGNAL(stateChanged(int)),     // signal
                     simple,                        // receiver
                     SLOT(setChanged(int)));        // slot

    dlg.show();
    return app.exec();
}


void Simple::setChanged(int val)
{
    if(label==NULL) return;
    QString text;
    text.sprintf("setChanged: %d", val);
    label->setText(text);
}
