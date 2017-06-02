/*
  Stacks
  Special lists are made for putting new items in a specific part of the list
  and getting items from one specific part. The QStack class in which the stack
  class can be classified as a FIFO (last in, first out) list.

  Working with the stack, new items are added to or pushed onto it using push.
  The top method is used to look at the current item. The current item is
  returned and removed from the stack by calling pop. This is called popping the
  stack. Before trying to pop the stack, you can check whether there is
  something there to get by using the isEmpty method.

  $ which qmake
/usr/lib64/qt5/bin/qmake

  $ qmake -project -nopwd $PWD/13_stacks.cpp -o project.pro
  $ qmake
  $ make
  $ ./project
  $ git clean -f .
 */


#include <QStack>
#include <QString>
#include <QtDebug>


int main(int, char**)
{
	QStack<QString> stack;

	stack.push("foo");
	stack.push("bar");
	stack.push("baz");

	QString result;
	while(!stack.isEmpty())
		result += stack.pop();

	qDebug() << "result: " << result;

	return 0;
}
