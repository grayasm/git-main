/*
  Qt Core C++ Classes: http://doc.qt.io/qt-5/qtcore-module.html

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/08_qlist.cpp -o project.pro
  $ qmake
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
