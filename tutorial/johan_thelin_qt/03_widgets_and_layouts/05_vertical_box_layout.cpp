/*
  This sample does not contain a .ui file or a form.
  The size policy is applied directly from code.


  Build:
  qmake -project -nopwd $PWD/05_vertical_box_layout.cpp -o 05_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 05_project.pro
  make
  ./05_project
  git clean -f .
 */


#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QPushButton* bn1 = new QPushButton("foo");
    QPushButton* bn2 = new QPushButton("bar");
    QPushButton* bn3 = new QPushButton("baz");

    QVBoxLayout* vLayout = new QVBoxLayout(&dlg);
    vLayout->addWidget(bn1);
    vLayout->addWidget(bn3);
    vLayout->addWidget(bn2);

    dlg.show();

    return app.exec();
}
