/*
  A simple QComboBox sample.

  A combo box can be used like a list widget when only the current item is
  shown. An alternate use is to provide the users with a list of items, but
  also enable them to write their own texts. You control whether the user can
  type in custom text by using the editable property. When the user picks an
  item from the list, the activated(int) and activated(const QString&) signals 
  are emitted.


  Build:
  qmake -project -nopwd $PWD/14_QComboBox.cpp -o project.pro
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

    QComboBox* combobox = new QComboBox();
    QStringList items;
    items << "foo" << "bar" << "baz";
    combobox->addItems(items);

    QVBoxLayout* layout = new QVBoxLayout(&dlg);
    layout->addWidget(combobox);

    dlg.show();
    return app.exec();
}
