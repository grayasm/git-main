/*
  Build:
  qmake -project -nopwd $PWD/main.cpp              \
                        $PWD/DocumentWindow.cpp    \
                        $PWD/DocumentWindow.h      \
                        $PWD/MdiWindow.cpp         \
                        $PWD/MdiWindow.h           \
                        $PWD/images.qrc            \
                        -o 02_project.pro
  qmake -makefile -o Makefile "QT += widgets" 02_project.pro
  make
  ./02_project
  git clean -f .
 */


#include <QtWidgets/QApplication>
#include "MdiWindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MdiWindow win;
    MdiWindow.show();

    return app.exec();
}
