/*
  QQueue

  For the queue, the corresponding methods are enqueue for adding items,
  dequeue for pulling them out of the queue, and head for having a peek at
  the current item. Just as for the stack, there is a method called isEmpty
  that indicates whether there is anything enqueued.

  $ qmake-qt5 -project -nopwd $PWD/14_queues.cpp -o project.pro
  $ qmake-qt5
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QQueue>
#include <QString>
#include <QtDebug>


int main(int, char**)
{
	QQueue<QString> queue;

	queue.enqueue("foo");
	queue.enqueue("bar");
	queue.enqueue("baz");

	QString result;
	while(!queue.isEmpty())
		result += queue.dequeue();

	qDebug() << "result: " << result;

	return 0;
}
