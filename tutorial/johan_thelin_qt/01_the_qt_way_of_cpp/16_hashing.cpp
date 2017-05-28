/*
  QHash

  The QHash class can be used in the same way as QMap, but the order of the keys
  is arbitrary. The type used for keys in a hash must have the == operator and
  a global function called qHash.
  The qHash function should return an unsigned integer called a hash key that
  is used for looking up items in the hash list. The only requirement for the
  function is that it should always return the same value for the same data.
  Qt provides such functions for the most common types, but you must provide
  such a function if you want to put your own classes in a hash list.
  The performance of the hash list depends on the number of collisions that it
  can expect; that is, the number of keys that yields the same hash key.
  By using your knowledge of the keys that might appear, you can use the hash
  function to increase performance.

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/16_hashing.cpp -o project.pro
  $ qmake
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QHash>
#include <QString>
#include <QtDebug>


class Person
{
public:
    Person(const QString& name, const QString& number)
        : m_name(name),
          m_number(number)
    {
    }

    const QString& name() const { return m_name; }
    const QString& number() const { return m_number; }

private:
    QString m_name;
    QString m_number;
}; // Person

/* QHas container requires a global operator== and a qHash function. */
bool operator==(const Person& a, const Person& b)
{
    return (a.name() == b.name()) && (a.number() == b.number());
}

uint qHash(const Person& key)
{
    return qHash(key.name()) ^ qHash(key.number());
}


int main(int, char**)
{
    //    Key,    T
    QHash<Person, int> hash;

    hash[ Person("Anders", "8447070")] = 10;
    hash[ Person("Micke", "7728433")] = 20;

    qDebug() << hash.value( Person("Anders", "8447070")); // 10
    qDebug() << hash.value( Person("Anders", "8447071")); // 0
    qDebug() << hash.value( Person("Micke", "7728433"));  // 20
    qDebug() << hash.value( Person("Michael", "7728433"));// 0

    return 0;
}
