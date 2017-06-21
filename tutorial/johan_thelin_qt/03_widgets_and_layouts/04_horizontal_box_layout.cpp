/*
  This sample does not contain a .ui file or a form.
  The size policy is applied directly from code.


  Build:
  qmake -project -nopwd $PWD/04_horizontal_box_layout.cpp -o 04_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 04_project.pro
  make
  ./04_project
  git clean -f .
 */


#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QPushButton* bn1 = new QPushButton("foo");
    QPushButton* bn2 = new QPushButton("bar");
    QPushButton* bn3 = new QPushButton("baz");

    QHBoxLayout* hLayout = new QHBoxLayout(&dlg);
    hLayout->addWidget(bn1);
    hLayout->addWidget(bn3);
    hLayout->addWidget(bn2);

    dlg.show();

    return app.exec();
}
