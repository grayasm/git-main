/*
  Qt Core C++ Classes: http://doc.qt.io/qt-5/qtcore-module.html

  $ qmake-qt5 -project -nopwd $PWD/08_qlist.cpp -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .
 */

#include <QList>
#include <QString>
#include <QtDebug>

int main(int, char**)
{
	QList<QString> list;

	list << "foo" << "bar" << "baz";

	foreach( QString s, list)
		qDebug() << s;

	return 0;
}
