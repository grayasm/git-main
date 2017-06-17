/*
  Validating Text

  Because regular expressions are very useful for verifying that a given string
  has the correct format, it is natural that Qt has a validator based on it.
  The QRegExpValidator takes a QRegExp as a constructor argument and uses the RE
  to validate input.

  Build:
  qmake -project -nopwd $PWD/31_QRegExpValidator.cpp -o project.pro
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

    QGridLayout* layout = new QGridLayout(&dlg);
    QLabel* reLabel = new QLabel("Phone:");
    QLineEdit* reEdit = new QLineEdit("+46(0)31-445566");
    QPushButton* button = new QPushButton("Close");

    layout->addWidget(reLabel, 0, 0);
    layout->addWidget(reEdit, 0, 1);
    layout->addWidget(button, 1, 0, 1, 2);


    QRegExp re("^\\+\\d{1,2}\\([089]\\)\\d{2,5}\\-\\d+$");
    QRegExpValidator reValidator(re);

    reEdit->setValidator(&reValidator);

    dlg.show();
    return app.exec();
}
