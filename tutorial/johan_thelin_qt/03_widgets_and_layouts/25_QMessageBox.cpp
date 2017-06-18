/*
  Messages

  The QMessageBox class is used to show messages to the users (it can also be
  used to ask basic questions such as Do you want to save the file?)
  The static methods information, warning, and critical accept the same
  arguments and work the same way. The difference is the displayed icon and
  the system sound.

  Build:
  qmake -project -nopwd $PWD/25_QMessageBox.cpp -o 25_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 25_project.pro
  make
  ./25_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include <iostream>


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

    int ret = QMessageBox::question(NULL,
                                    QObject::tr("title"),
                                    QObject::tr("Answer the question."),
                                    QMessageBox::Yes |
                                    QMessageBox::No |
                                    QMessageBox::Cancel |
                                    QMessageBox::Ignore);
    switch(ret)
    {
    case QMessageBox::Yes:
	    std::cout << "QMessageBox::Yes\n";
	    break;

    case QMessageBox::No:
	    std::cout << "QMessageBox::No\n";
	    break;

    case QMessageBox::Cancel:
	    std::cout << "QMessageBox::Cancel\n";
	    break;

    case QMessageBox::Ignore:
	    std::cout << "QMessageBox::Ignore\n";
	    break;
    };

    // no need for the message loop, just return to system
    // return app.exec();
    return 0;
}
