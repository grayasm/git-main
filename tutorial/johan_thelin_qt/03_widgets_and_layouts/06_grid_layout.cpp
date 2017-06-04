/*
  This sample does not contain a .ui file or a form.
  Grid layout and widgets placement is done in the code.

  Build instructions:
  qmake -project -nopwd $PWD/06_grid_layout.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QPushButton* bn1 = new QPushButton("foo");
    QPushButton* bn2 = new QPushButton("bar");
    QPushButton* bn3 = new QPushButton("baz");

    QGridLayout layout(&dlg);
    layout.addWidget(bn1, 0, 0, 1, 2); // row, col, rowspan, colspan
    layout.addWidget(bn2, 1, 0);
    layout.addWidget(bn3, 1, 1);

    dlg.show();

    return app.exec();
}
