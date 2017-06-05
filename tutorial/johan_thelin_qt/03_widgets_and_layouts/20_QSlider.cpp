/*
  Simple QSlider sample, with signal connected to a QLCDNumber slot.


  Build:
  qmake -project -nopwd $PWD/20_QSlider.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */

#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QLCDNumber* number = new QLCDNumber();
    QSlider* slider = new QSlider(Qt::Horizontal);
    QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                 QDialogButtonBox::Cancel);

    QVBoxLayout* layout = new QVBoxLayout(&dlg);
    layout->addWidget(number);
    layout->addWidget(slider);
    layout->addWidget(box);

    QObject::connect(slider,                        // sender
                     SIGNAL(valueChanged(int)),     // signal
                     number,                        // receiver
                     SLOT(display(int)));           // slot

    slider->setRange(0, 100);

    dlg.show();
    return app.exec();
}
