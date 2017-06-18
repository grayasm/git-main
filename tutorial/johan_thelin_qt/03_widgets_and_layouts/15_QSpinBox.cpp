/*
  Simple QSpinBox sample, with signal connected to a QLCDNumber slot.


  Build:
  qmake -project -nopwd $PWD/15_QSpinBox.cpp -o 15_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 15_project.pro
  make
  ./15_project
  git clean -f .
 */

#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QLCDNumber* number = new QLCDNumber();
    QSpinBox* spin = new QSpinBox();
    QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                 QDialogButtonBox::Cancel);

    QVBoxLayout* layout = new QVBoxLayout(&dlg);
    layout->addWidget(number);
    layout->addWidget(spin);
    layout->addWidget(box);

    QObject::connect(spin,                          // sender
                     SIGNAL(valueChanged(int)),     // signal
                     number,                        // receiver
                     SLOT(display(int)));           // slot

    spin->setRange(0, 100);

    dlg.show();
    return app.exec();
}
