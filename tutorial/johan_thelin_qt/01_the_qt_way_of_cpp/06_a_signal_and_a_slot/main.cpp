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
