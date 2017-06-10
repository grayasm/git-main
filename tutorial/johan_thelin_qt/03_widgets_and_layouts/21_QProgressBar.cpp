/*
  Simple QProgressBar sample, written with QtCreator.
  Used Edit Signal tab to set the signals.
  The progress bar text formatting recognizes:
  %v - current value
  %m - maxim value
  %p - current percentage
  ex: %v out of %m steps completed

  By setting minimum and maximum to 0, the progress bar keeps moving continuosly


  Build:
  qmake -project -nopwd $PWD/21_QProgressBar.cpp \
                        $PWD/21_Form.cpp $PWD/21_Form.h $PWD/21_Form.ui \
                        -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include "21_Form.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Dialog dlg;

    dlg.show();
    return app.exec();
}
