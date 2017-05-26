/*
  QMultiMap

  This section discusses the QMultiMap class, but all that I say also applies
  to the QMultiHash class. The QMultiMap class does not have a [] operator;
  instead, the insert method is used for adding values and the method values
  for accessing the inserted items. Because the QMultiMap can contain multiple
  elements for a key, the values method returns a QList with the items
  associated with the given key. Before requesting a list, it is possible to
  see how many items are associated to a given key using the count method.

  $ qmake-qt5 -project -nopwd $PWD/18_qmultimap.cpp -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QMultiMap>
#include <QString>
#include <QtDebug>


int main(int, char**)
{
    QMultiMap<QString, int> multi;

    multi.insert("foo", 10);
    multi.insert("foo", 20);
    multi.insert("bar", 30);

    /*
     * Finding the unique keys and then iterating over each key and its
     * associated items.
     */
    QSet<QString> keys = QSet<QString>::fromList(multi.keys());

    foreach(QString key, keys)
        foreach(int value, multi.values(key))
            qDebug() << key << " : " << value;

    /*
     * There is a quicker way to find all the items in a QMultiMap: use an
     * iterator. A QMultiMap::iterator has the member functions key and value,
     * which are used to get the information that it contains.
     * The iterator approach also avoids having to build a list with all the
     * items belonging to the key, which is what happens when you use the
     * values method—saving both memory and time.
     */
    QMultiMap<QString, int>::ConstIterator ii = multi.find("foo");
    while(ii != multi.end() && ii.key() == "foo")
    {
        qDebug() << ii.value();
        ++ii;
    }

    return 0;
}
