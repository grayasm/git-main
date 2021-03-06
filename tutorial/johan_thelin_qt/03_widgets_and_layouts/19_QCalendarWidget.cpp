/*
  Simple QCalendarWidget sample.


  Build:
  qmake -project -nopwd $PWD/19_QCalendarWidget.cpp -o 19_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 19_project.pro
  make
  ./19_project
  git clean -f .
 */

#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QCalendarWidget* time = new QCalendarWidget();

    QVBoxLayout* layout = new QVBoxLayout(&dlg);

    layout->addWidget(time);

    dlg.show();
    return app.exec();
}
