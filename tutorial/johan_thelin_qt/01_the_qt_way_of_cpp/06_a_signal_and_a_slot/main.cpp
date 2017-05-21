/*
  See MyClass.h for the explation for 'signals, slots and meta-objects'.

  connect:  it asks the meta-object to add the slot to the signal's calling list.
            if the arguments match, the connection is made.
            when matching arguments, the match is checked only for the arguments
            accepted by the slot. A slot that does not take any arguments
            matches all signals. The arguments not accepted by the slot are
            simply dropped by the signal-emitting code.

  $ qmake-qt5 -project
  $ qmake
  $ make
 */
#include "MyClass.h"

int main(int, char**)
{
	QObject parent;

	MyClass *a, *b, *c;

	a = new MyClass( "foo", &parent );
	b = new MyClass( "bar", &parent );
	c = new MyClass( "baz", &parent );

	QObject::connect(
		a, SIGNAL(textChanged(const QString&)),
		b, SLOT(setText(const QString&)) );

	QObject::connect(
		b, SIGNAL(textChanged(const QString&)),
		c, SLOT(setText(const QString&)) );

	QObject::connect(
		c, SIGNAL(textChanged(const QString&)),
		b, SLOT(setText(const QString&)) );


	b->setText("test");
	a->setText("Qt");

	return 0;
}
