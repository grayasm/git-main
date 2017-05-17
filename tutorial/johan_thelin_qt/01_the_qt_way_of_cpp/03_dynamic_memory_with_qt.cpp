/*
  This example uses a parent that is automatically deleted when the main
  function exits. The parent is responsible for calling delete for all children
  and—ta-da!—the memory is freed.

  The parent object is added to show the concept. In real life, it would be an
  object performing some sort of task—for example, a QApplication object, or
  (in the case of a dialog box or a window) the this pointer of the window
  class.
 */


#include <iostream>
#include <string>

#include <QObject>
#include <QString>
#include <QtDebug>

using std::string;

class MyClass : public QObject
{
public:
	MyClass(const string& text, QObject* parent = 0) : QObject(parent)
	{
		m_text = text;
		std::cout << "ctor " << m_text.c_str() << std::endl;
	}

	~MyClass()
	{
		std::cout << "dtor " << m_text.c_str() << std::endl;
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
	QObject parent;
	MyClass *a, *b, *c;

	a = new MyClass("foo", &parent);
	b = new MyClass("ba-a-ar", &parent);
	c = new MyClass("baz", &parent);

	qDebug() << QString::fromStdString(a->text()) << " (" <<
		a->getLengthOfText() << ")";

	a->setText(b->text());

	qDebug() << QString::fromStdString(a->text()) << " (" <<
		a->getLengthOfText() << ")";

	return a->getLengthOfText() - c->getLengthOfText();
}
