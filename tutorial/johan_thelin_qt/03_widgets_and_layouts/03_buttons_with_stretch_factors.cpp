/*
  This sample does not contain a .ui file or a form.
  The size policy is applied directly from code.


  Build:
  qmake -project -nopwd $PWD/03_buttons_with_stretch_factors.cpp \
                 -o 03_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 03_project.pro
  make
  ./03_project
  git clean -f .
 */


#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QGroupBox* groupBox = new QGroupBox("Groupbox");
    QPushButton* bn1 = new QPushButton("stretch = 1");
    QPushButton* bn2 = new QPushButton("stretch = 2");
    QPushButton* bn3 = new QPushButton("stretch = 3");


    QHBoxLayout* hLayout = new QHBoxLayout(groupBox);
    hLayout->addWidget(bn1);
    hLayout->addWidget(bn3);
    hLayout->addWidget(bn2);

    QVBoxLayout* vLayout = new QVBoxLayout(&dlg);
    vLayout->addWidget(groupBox);

    QSizePolicy policy = bn1->sizePolicy();
    policy.setHorizontalStretch(1);
    bn1->setSizePolicy(policy);

    policy = bn2->sizePolicy();
    policy.setHorizontalStretch(2);
    bn2->setSizePolicy(policy);

    policy = bn3->sizePolicy();
    policy.setHorizontalStretch(3);
    bn3->setSizePolicy(policy);

    dlg.show();

    return app.exec();
}
