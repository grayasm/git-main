/*
  List of Strings
  The string list class inherits QList<QString> and can be treated as such.
  However, it also has some string-specific methods that make it useful.

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/12_list_of_strings.cpp -o project.pro
  $ qmake
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QtDebug>
#include <QStringList>


int main(int, char**)
{
	QStringList list;

	list << "foo" << "bar" << "baz";

	QString all = list.join(",");
	qDebug() << "all=" << all;

	list.replaceInStrings("a", "oo");

	list << all.split(",");

	for(QStringList::iterator it = list.begin(); it != list.end(); ++it)
		qDebug() << *it;

	return 0;
}
