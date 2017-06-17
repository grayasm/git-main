/*
  Fonts

  The QFontDialog class is used when you need to let the user pick a font.
  The static getFont method shows the dialog and returns a QFont.

  Because a font cannot be invalid, the arguments to the method start with a
  Boolean value that indicates whether the user canceled the dialog. The value
  true indicates that the returned font has been accepted by the user.
  The second argument is a QFont to start from. The third argument is a parent
  widget, and the last argument is a window title for the dialog.

  Build:
  qmake -project -nopwd $PWD/28_QFontDialog.cpp -o project.pro
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

    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,                      // button
                                      QFont("Arial", 18),       // initial
                                      NULL,                     // parent
                                      QObject::tr("Title"));    // title
    if(ok)
        std::cout << "getFont=" << font.toString().toStdString() << std::endl;


    // no need for the message loop, return to system
    return 0;
}
