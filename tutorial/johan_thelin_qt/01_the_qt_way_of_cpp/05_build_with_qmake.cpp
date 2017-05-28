/*
  Qt comes with the QMake tool, which can create Makefiles for a range of
  different compilers. It even creates the project definition file for you if
  you want it to.

  doc: http://doc.qt.io/qt-4.8/qmake-running.html#projectmode

  Build and run the project with:

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/05_build_with_qmake.cpp -o project.pro
  $ qmake
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
