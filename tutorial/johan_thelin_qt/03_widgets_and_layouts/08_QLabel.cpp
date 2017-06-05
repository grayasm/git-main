/*
  QLabel mnemonic (keyboard shortcut) is ALT+A : setText("Your &Age")
  QLabel associated widget to receive the focus: setBuddy(ageEdit)


  Build with:
  qmake -project -nopwd $PWD/08_QLabel.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QLabel* fooLabel = new QLabel("&Foo:");
    QLabel* barLabel = new QLabel("&Bar:");

    QLineEdit* fooEdit = new QLineEdit();
    QLineEdit* barEdit = new QLineEdit();

    fooLabel->setBuddy(fooEdit);
    barLabel->setBuddy(barEdit);

    QGridLayout* layout = new QGridLayout(&dlg);
    layout->addWidget(fooLabel, 0, 0);
    layout->addWidget(fooEdit, 0, 1);
    layout->addWidget(barLabel, 1, 0);
    layout->addWidget(barEdit, 1, 1);

    dlg.show();


    return app.exec();
}
