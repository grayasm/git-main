/*
  The size policies are applied directly in the Qt ui designer.

  Build with:
  qmake -project -nopwd $PWD/01_size_policies_designer.cpp \
                        $PWD/01_designerdlg.cpp	  \
                        $PWD/01_designerdlg.h	  \
                        $PWD/01_designerdlg.ui	  \
                        -o designer.pro
  qmake -makefile -o Makefile "QT+=widgets" designer.pro
  make
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
