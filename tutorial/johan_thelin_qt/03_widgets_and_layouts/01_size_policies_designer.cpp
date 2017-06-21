/*
  The size policies are applied directly in the Qt ui designer.


  Build:
  qmake -project -nopwd $PWD/01_size_policies_designer.cpp \
                        $PWD/01_designerdlg.cpp	  \
                        $PWD/01_designerdlg.h	  \
                        $PWD/01_designerdlg.ui	  \
                        -o 01_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 01_project.pro
  make
  ./01_project
  git clean -f .
 */


#include "01_designerdlg.h"
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    DesignerDlg dlg;
    dlg.show();

    return app.exec();
}
