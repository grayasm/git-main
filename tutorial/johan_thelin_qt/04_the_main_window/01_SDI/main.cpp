/*
  Build:
  qmake -project -nopwd $PWD/main.cpp        \
                        $PWD/SdiWindow.cpp   \
                        $PWD/SdiWindow.h     \
                        $PWD/images.qrc      \
                        -o 01_project.pro
  qmake -makefile -o Makefile "QT += widgets" 01_project.pro
  make
  ./01_project
  git clean -f .
 */


#include "SdiWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    SdiWindow* ptr = new SdiWindow(NULL);
    ptr->show();

    return app.exec();
}
