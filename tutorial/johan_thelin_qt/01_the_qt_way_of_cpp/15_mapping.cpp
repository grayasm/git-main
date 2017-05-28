/*
  QMap
  QMap class enables you to keep items in key-value pairs.

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/15_mapping.cpp -o project.pro
  $ qmake
  $ make
  $ ./project
  $ git clean -f .
*/


#include <QMap>
#include <QString>
#include <QtDebug>


int main(int, char**)
{
	QMap<QString, int> map;

    map["foo"] = 42;
    map["bar"] = 13;
    map["baz"] = 9;


    // showing all key-value pairs on the debugging console
    foreach(QString key, map.keys())
        qDebug() << key << " = " << map[key];

    // iterating over all key-value pairs
    QMap<QString, int>::ConstIterator ii;
    for(ii = map.constBegin(); ii != map.constEnd(); ++ii)
	    qDebug() << ii.key() << " = " << ii.value();

    return 0;
}
