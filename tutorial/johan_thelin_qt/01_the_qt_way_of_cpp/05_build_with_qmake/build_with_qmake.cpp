/*
  Qt comes with the QMake tool, which can create Makefiles for a range of
  different compilers. It even creates the project definition file for you if
  you want it to.

  Create .pro file with:
  $ qmake-qt5 -project

  Then generate the Makefile with:
  $ qmake-qt5

  To build and run the program type:
  $ make
  $ ./05_build_with_qmake

  Clean with:
  $ git clean -f .
 */


#include <QtDebug>

int main()
{
	qDebug() << "Hello Qt World!";

	return 0;
}
