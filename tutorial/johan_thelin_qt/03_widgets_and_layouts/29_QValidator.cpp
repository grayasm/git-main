/*
  Validating User Input

  QValidator class validates user input in QLineEdit and QComboBox widgets.
  It validates a string, with status Invalid, Intermediate or Acceptable.
  Invalid string cannot be converted.
  An Intermediate string can be converted to Acceptable.

  For numbers there are only 2 classes: QIntValidator and QDoubleValidator.
  To assign a validator QLineEdit and QComboBox have setValidator(QValidator*).

  Build:
  qmake -project -nopwd $PWD/29_QValidator.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  git clean -f .
 */


#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QGridLayout* layout = new QGridLayout(&dlg);
    QLineEdit* intEdit = new QLineEdit("42");
    QLineEdit* doubleEdit = new QLineEdit("3.14");
    QPushButton* button = new QPushButton("Close");

    QLabel* intLabel = new QLabel("Integer:");
    QLabel* doubleLabel = new QLabel("Double:");


    layout->addWidget(intLabel, 0, 0);
    layout->addWidget(intEdit, 0, 1);
    layout->addWidget(doubleLabel, 1, 0);
    layout->addWidget(doubleEdit, 1, 1);
    layout->addWidget(button, 2, 0, 1, 2);

    // no connection, gave up to write a 29_QValidator.h for it.

    QIntValidator intValidator(0, 100);              // bottom, top
    QDoubleValidator doubleValidator(0.0, 100.0, 3); // bottom, top, decimals

    intEdit->setValidator(&intValidator);
    doubleEdit->setValidator(&doubleValidator);

    dlg.show();
    return app.exec();
}
