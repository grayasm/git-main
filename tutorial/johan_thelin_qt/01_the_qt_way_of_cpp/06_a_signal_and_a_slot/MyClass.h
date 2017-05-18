#include <QObject>
#include <QString>
#include <QtDebug>

class MyClass : public QObject
{
	Q_OBJECT

public:
	MyClass(const QString& text, QObject* parent = 0) : QObject(parent)
	{
		m_text = text;
	}

	const QString& text() const
	{
		return m_text;
	}

	int getLengthOfText() const
	{
		return m_text.size();
	}

public slots:
	void setText(const QString& text)
	{
		qDebug() << __FUNCTION__ << ": " << text;

		if(m_text == text)
			return;

		m_text = text;

		emit textChanged(m_text);
	}

signals:
	void textChanged(const QString&);

private:
	QString m_text;
};
