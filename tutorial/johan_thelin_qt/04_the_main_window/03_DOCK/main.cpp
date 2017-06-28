/*
  Build:
  qmake -project -nopwd $PWD/main.cpp         \
                        $PWD/SdiWindow.cpp    \
                        $PWD/SdiWindow.h      \
                        $PWD/InfoWidget.cpp   \
                        $PWD/InfoWidget.h     \
                        $PWD/images.qrc       \
                        -o 03_project.pro
  qmake -makefile -o Makefile "QT += widgets" 03_project.pro
  make
  ./03_project
  git clean -f .
 */


#include "SdiWindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    SdiWindow* ptr = new SdiWindow();
    ptr->show();

    return app.exec();
}
