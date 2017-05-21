/*
  Qt Core C++ Classes:  http://doc.qt.io/qt-5/qtcore-module.html
  QList:                http://doc.qt.io/qt-5/qlist.html
  QLinkedList:          http://doc.qt.io/qt-5/qlinkedlist.html
  QByteArrayList:       http://doc.qt.io/qt-5/qbytearraylist.html
  QStringList:          http://doc.qt.io/qt-5/qstringlist.html

  QListIterator:        http://doc.qt.io/qt-5/qlistiterator.html
  QMutableListIterator  http://doc.qt.io/qt-5/qmutablelistiterator.html

  $ qmake-qt5 -project -nopwd $PWD/09_stl_and_java_style_iterators.cpp \
                       -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .

 */

#include <QList>
#include <QtDebug>
#include <QListIterator>


int main(int, char**)
{
	QList<int> list;

	list << 23 << 27 << 52 << 52;

	QListIterator<int> javaIter (list);
	while(javaIter.hasNext())
		qDebug() << javaIter.next();

	QList<int>::const_iterator stlIter;
	for (stlIter = list.begin(); stlIter != list.end(); ++stlIter)
		qDebug() << (*stlIter);


	return 0;
}
