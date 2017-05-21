/*
  Qt comes with the QMake tool, which can create Makefiles for a range of
  different compilers. It even creates the project definition file for you if
  you want it to.

  doc: http://doc.qt.io/qt-4.8/qmake-running.html#projectmode

  Build and run the project with:

  $ qmake-qt5 -project -nopwd $PWD/05_build_with_qmake.cpp -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QtDebug>

int main()
{
	qDebug() << "Hello Qt World!";

	return 0;
}
