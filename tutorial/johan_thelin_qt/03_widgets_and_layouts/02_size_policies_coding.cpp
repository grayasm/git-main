/*
  This sample does not contain a .ui file or a form.
  The size policy is applied directly from code.

  Build instructions:
  qmake -project -nopwd $PWD/02_size_policies_coding.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QGroupBox* groupBox = new QGroupBox("Groupbox");
    QLabel* label = new QLabel("Supercalifragilisticexpialidocious");
    QLineEdit* lineEdit = new QLineEdit;
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                     QDialogButtonBox::Cancel);

    QHBoxLayout* hLayout = new QHBoxLayout(groupBox);
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);

    QVBoxLayout* vLayout = new QVBoxLayout(&dlg);
    vLayout->addWidget(groupBox);
    vLayout->addStretch();
    vLayout->addWidget(buttons);

    QSizePolicy policy = label->sizePolicy();
    policy.setHorizontalStretch(3);
    label->setSizePolicy(policy);

    policy = lineEdit->sizePolicy();
    policy.setHorizontalStretch(1);
    lineEdit->setSizePolicy(policy);

    dlg.show();

    return app.exec();
}
