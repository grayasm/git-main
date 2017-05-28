/*
  Modifying lists using iterators.

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/10_modifying_a_qlist.cpp -o project.pro
  $ qmake
  $ make
  $ ./project
  $ git clean -f .
 */

#include <QtDebug>
#include <QList>
#include <QMutableListIterator>


int main(int, char**)
{
	QList<int> list;

	list << 27 << 33 << 61 << 62;

	QMutableListIterator<int> javaIter(list);
	while (javaIter.hasNext())
	{
		int value = javaIter.next() + 1;
		javaIter.setValue(value);
		qDebug() << value;
	}


	QList<int>::Iterator stlIter;
	for (stlIter = list.begin(); stlIter != list.end(); ++stlIter)
	{
		(*stlIter) = (*stlIter)*2;
		qDebug() << (*stlIter);
	}

	return 0;
}
