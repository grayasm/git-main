/*
  QMultiHash

  The only possible difference in outcome (compared with QHash) is that the
  keys are returned in an arbitrary order. Notice that this does not mean that
  the find and iterate method fails—the keys appear in an arbitrary order, but
  are still in order.

  $ qmake-qt5 -project -nopwd $PWD/19_qmultihash.cpp -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QMultiHash>
#include <QString>
#include <QSet>
#include <QtDebug>


int main(int, char**)
{
    QMultiHash<QString, int> multi;

    multi.insert( "foo", 10 );
    multi.insert( "foo", 20 );
    multi.insert( "bar", 30 );

    QSet<QString> keys = QSet<QString>::fromList(multi.keys());

    foreach( QString key, keys )
        foreach( int value, multi.values(key) )
            qDebug() << key << ": " << value;

    QMultiHash<QString, int>::ConstIterator ii = multi.find( "foo" );
    while( ii != multi.end() && ii.key() == "foo" )
    {
        qDebug() << ii.value();
        ++ii;
    }

    return 0;
}
