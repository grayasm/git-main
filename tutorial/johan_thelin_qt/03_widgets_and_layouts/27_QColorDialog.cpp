/*
  Colors

  The QColorDialog class is used to enable the user to pick a color.
  The call to QColorDialog::getColor accepts a QColor as a starting value
  and a parent. The return value is a QColor that is invalid if the user
  has cancelled the dialog.

  Build:
  qmake -project -nopwd $PWD/27_QColorDialog.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include <iostream>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QColor color = QColorDialog::getColor(Qt::yellow,               // initial
                                          NULL,                     // parent
                                          QObject::tr("Title"));    // title

    if (color.isValid())
        std::cout << "getColor=" << color.red() <<
                     ", " << color.green() <<
                     ", " << color.blue() << std::endl;



    // no need for the message loop, return to system
    return 0;
}
