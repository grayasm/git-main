/*
  Simple QDateEdit sample.


  Build:
  qmake -project -nopwd $PWD/17_QDateEdit.cpp -o 17_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 17_project.pro
  make
  ./17_project
  git clean -f .
 */

#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QDateEdit* time = new QDateEdit();

    QVBoxLayout* layout = new QVBoxLayout(&dlg);

    layout->addWidget(time);

    dlg.show();
    return app.exec();
}
