/*
  The size policies are applied directly in the Qt ui designer.
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
