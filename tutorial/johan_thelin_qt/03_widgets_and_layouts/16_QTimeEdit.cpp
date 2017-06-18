/*
  Simple QTimeEdit sample.


  Build:
  qmake -project -nopwd $PWD/16_QTimeEdit.cpp -o 16_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 16_project.pro
  make
  ./16_project
  git clean -f .
 */

#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QTimeEdit* time = new QTimeEdit();

    QVBoxLayout* layout = new QVBoxLayout(&dlg);

    layout->addWidget(time);

    dlg.show();
    return app.exec();
}
