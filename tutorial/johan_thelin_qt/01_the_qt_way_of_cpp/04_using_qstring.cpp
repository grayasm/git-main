/*
  Another step toward using Qt is to replace any classes from the C++ standard
  template library (STL) with the corresponding Qt class. Although it is not
  required (Qt works great alongside the STL), it does make it possible to
  avoid having to rely on a second framework.
  The benefit of not using the STL is that you use the same containers, strings,
  and helpers as Qt does, so the resulting application will most likely be
  smaller. You also avoid having to track down compatibility issues and strange
  deviations from the STL standard when moving between platforms and compilers —
  you can even develop on platforms that do not have implementations of the
  STL (mobile?)
 */

#include <QString>
#include <QObject>
#include <QtDebug>



class MyClass : public QObject
{
public:
	MyClass(const QString& text, QObject* parent = 0) : QObject(parent)
	{
		m_text = text;
	}

	const QString& text() const
	{
		return m_text;
	}

	void setText(const QString& text)
	{
		m_text = text;
	}

	int getLengthOfText() const
	{
		return m_text.size();
	}

private:
	QString m_text;
};


int main(int, char**)
{
	QObject parent;
	MyClass *a, *b, *c;

	a = new MyClass("foo", &parent);
	b = new MyClass("ba-a-ar", &parent);
	c = new MyClass("baz", &parent);

	qDebug() << a->text() << " (" << a->getLengthOfText() << ")";
	a->setText(b->text());
	qDebug() << a->text() << " (" << a->getLengthOfText() << ")";

	return a->getLengthOfText() - c->getLengthOfText();
}
