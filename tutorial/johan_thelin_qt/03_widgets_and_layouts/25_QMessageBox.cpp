/*
  Messages

  The QMessageBox class is used to show messages to the users (it can also be
  used to ask basic questions such as Do you want to save the file?)
  The static methods information, warning, and critical accept the same
  arguments and work the same way. The difference is the displayed icon and
  the system sound.

  Build:
  qmake -project -nopwd $PWD/25_QMessageBox.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
 */


#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMessageBox::information(NULL,
                             QObject::tr("title"),
                             QObject::tr("An information message."));

    QMessageBox::warning(NULL,
                         QObject::tr("title"),
                         QObject::tr("A warning message."));

    QMessageBox::critical(NULL,
                          QObject::tr("title"),
                          QObject::tr("A critical message."));

    // no need for the message loop, just return to system
    // return app.exec();
    return 0;
}
