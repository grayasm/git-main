/*
  Demonstrate QLineEdit properties (maxLength and EchoMode).
  09_Form.ui is edited in QtCreator.
  All QLineEdit(s) from 2nd column are drag&dropped over 3rd column, with
  signal-slot connection: textChanged(QString)->setText(QString).


  Build:
  qmake -project -nopwd $PWD/09_QLineEdit.cpp \
                        $PWD/09_Form.cpp      \
                        $PWD/09_Form.h        \
                        $PWD/09_Form.ui       \
                        -o 09_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 09_project.pro
  make
  ./09_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include "09_Form.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Dialog dlg;
    dlg.show();
    return app.exec();
}
