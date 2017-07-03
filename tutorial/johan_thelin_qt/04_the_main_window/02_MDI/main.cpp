/*
  Sample at: https://github.com/Apress/foundations-of-qt-dev/blob/master/Chapter04/mdi/mdiwindow.cpp
  uses QWorkspace which was removed in Qt5 and replaced with QMdiArea.
  I made the sample compile with QMdiArea but cut,copy,paste actions trigger
  segmentation fault. I did not take time to fix this.


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
    win.show();

    return app.exec();
}
