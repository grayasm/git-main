/*
  Filling the List
  << operator used appends new data to the end of the list. It is possible to
  prepend data (add at the start of the list) or insert data in the middle.

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/11_append_prepend_insert.cpp -o project.pro
  $ qmake
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QtDebug>
#include <QList>
#include <QString>


int main(int, char**)
{
	QList<QString> list;


	list << "first";
	list.append("second");
	list.append("third");
	list.insert(1, "fourth");
	list.insert(4, "fifth");

	for(QList<QString>::const_iterator it = list.begin(); it != list.end(); ++it)
		qDebug() << *it;


	return 0;
}
