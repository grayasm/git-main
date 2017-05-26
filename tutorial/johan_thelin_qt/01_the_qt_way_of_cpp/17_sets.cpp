/*
  QSet

  Sometimes the interesting thing is not mapping a value to a key, but
  remembering which keys are valid. In this situation, you can use the QSet
  class. A set is a hash without the value, so there must be a qHash function
  and a == operator for the keys. Also, the order of the keys is arbitrary.

  $ qmake-qt5 -project -nopwd $PWD/17_sets.cpp -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QSet>
#include <QString>
#include <QtDebug>


int main(int, char**)
{
    QSet<QString> set;

    set << "Ada" << "C++" << "Ruby";

    for(QSet<QString>::ConstIterator ii = set.begin(); ii != set.end(); ++ii)
    {
        qDebug() << *ii;
    }

    if(set.contains("FORTRAN"))
        qDebug() << "FORTRAN is in the set.";
    else
        qDebug() << "FORTRAN is out.";

    return 0;
}
