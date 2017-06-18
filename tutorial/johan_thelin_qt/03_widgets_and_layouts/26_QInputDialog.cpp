/*
  Input Dialog

  If you need to ask slightly more advanced questions than Yes/No/Cancel,
  you can use the QInputDialog class. Using this class you can ask the user
  for values and texts, and to pick an item from a given list.

  Build:
  qmake -project -nopwd $PWD/26_QInputDialog.cpp -o 26_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 26_project.pro
  make
  ./26_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include <iostream>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // asking the user to enter some text
    bool ok = false;
    QString text = QInputDialog::getText(NULL,
                                         QObject::tr("Title"),
                                         QObject::tr("Enter a city name:"),
                                         QLineEdit::Normal,
                                         QObject::tr("Alingsås"),
                                         &ok);
    if(ok && !text.isEmpty())
        std::cout << "getText=" << text.toStdString() << std::endl;


    // asking the user to pick an item from a list
    ok = false;
    QStringList items;
    items << "Foo" << "Bar" << "Baz";
    QString item = QInputDialog::getItem(NULL,                    // parent
                                         QObject::tr("Title"),    // title
                                         QObject::tr("Pick an item:"), // label
                                         items,                   // items
                                         0,                       // current
                                         false,                   // editable
                                         &ok);                    // button ok
    if(ok && !item.isEmpty())
        std::cout << "getItem=" << item.toStdString() << std::endl;



    // asking the user for an integer value
    ok = false;
    int value = QInputDialog::getInt(NULL,                          // parent
                                     QObject::tr("Title"),          // title
                                     QObject::tr("Enger an angle:"),// label
                                     90,                            // current
                                     0,                             // min
                                     360,                           // max
                                     1,                             // step
                                     &ok);                          // button
    if(ok)
        std::cout << "getInt=" << value << std::endl;

    // no need for the message loop, return to system
    return 0;
}
