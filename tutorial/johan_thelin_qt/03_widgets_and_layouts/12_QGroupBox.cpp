/*
  You can use a group box to structure the contents of a dialog. It provides a
  frame with a title in which you can put other widgets. The group box is a
  passive widget that works only as a container for other widgets.

  If you want to be able to turn the option controlled by the widgets in the
  group box on or off, you can make it checkable using the checkable property
  (this means that a checkbox will be shown in the title). When the checkbox is
  unchecked, its contents are disabled, and users cannot use it.
  Checkable group boxes have the isChecked() method and the toggled(bool) signal


  Build:
  qmake -project -nopwd $PWD/12_QGroupBox.cpp -o project.pro
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

    QGroupBox box("Testing", &dlg);
    box.setFlat(true);

    QButtonGroup* group = new QButtonGroup(&box);
    QRadioButton* foo = new QRadioButton("foo");
    QRadioButton* bar = new QRadioButton("bar");
    QRadioButton* baz = new QRadioButton("baz");

    group->addButton(foo);
    group->addButton(bar);
    group->addButton(baz);

    QVBoxLayout* layout = new QVBoxLayout(&box);
    layout->addWidget(foo);
    layout->addWidget(bar);
    layout->addWidget(baz);

    dlg.show();
    return app.exec();
}
