/*
  The first Qt-specific adjustment you will make to the code is really simple:
  you will simply let your class inherit the QObject class, which will make it
  easier to manage instances of the class dynamically by giving instances
  parents that are responsible for their deletion.

  The parent argument is also added to the constructor as a convenience because
  QObject has a function, setParent, which can be used to assign an object
  instance to a parent after creation. However, it is common—and recommended—to
  pass the parent as an argument to the constructor as the first default
  argument to avoid having to type setParent for each instance created from the
  class.
 */

#include <iostream>
#include <string>

#include <QObject>

using std::string;

class MyClass : public QObject
{
public:
	MyClass(const string& text, QObject* parent = 0) : QObject(parent)
	{
		m_text = text;
	}

	const string& text() const
	{
		return m_text;
	}

	void setText(const string& text)
	{
		m_text = text;
	}

	int getLengthOfText() const
	{
		return m_text.size();
	}

private:
	string m_text;
};

int main(int, char**)
{
	MyClass *a, *b, *c;

	a = new MyClass("foo");
	b = new MyClass("ba-a-ar");
	c = new MyClass("baz");

	std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;
	a->setText(b->text());
	std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;

	int result = a->getLengthOfText() - c->getLengthOfText();

	/* In this example the memory is freed manually. */
	delete a;
	delete b;
	delete c;

	return result;
}
