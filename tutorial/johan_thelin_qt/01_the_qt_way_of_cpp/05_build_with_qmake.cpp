/*
  Qt comes with the QMake tool, which can create Makefiles for a range of
  different compilers. It even creates the project definition file for you if
  you want it to.

  Open a command line and type:
  $ qmake-qt5 -project
  $ emacs 01_the_qt_way_of_cpp.pro

  Change the project file as follows:
  TARGET = 05_build_with_qmake
  SOURCES += 05_build_with_qmake.cpp

  To generate the Makefile type:
  $ qmake-qt5

  To build and run the program type:
  $ make
  $ ./05_build_with_qmake

  To clean the directory:
  $ git clean -f .
 */


#include <QtDebug>

int main()
{
	qDebug() << "Hello Qt World!";

	return 0;
}
