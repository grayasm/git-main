/*
  Simple QDateTimeEdit sample.


  Build:
  qmake -project -nopwd $PWD/18_QDateTimeEdit.cpp -o 18_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 18_project.pro
  make
  ./18_project
  git clean -f .
 */

#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QDateTimeEdit* time = new QDateTimeEdit();

    QVBoxLayout* layout = new QVBoxLayout(&dlg);

    layout->addWidget(time);

    dlg.show();
    return app.exec();
}
