/*
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
