/*
  Signal, Slots and the Meta-Objects.

  signal: a method that is emitted rather than executed when called.
          declared as a prototype by the developer in a header file (HEADER only).
          implementation is generated at compile time by moc, meta-object compiler.

  slot:   a member function that is invoked as a result of a signal emmission.
          slots can be 'public slots', 'protected slots' or 'private slots'
          implementation is done by developer and method can still be called
          normally or as a result of a signal emission.

  Q_OBJECT: must appear first in the body of the class declaration (HEADER only).
            implementation is generated at compile time by moc.
            creates a QMetaObject instance with information about the class such
            as: name, super classes, signals, slots and other things.

  emit:   called with the signal as argument.
          it is replaced by the moc with actual call to signal function.

  A Qt tool called 'the meta-object compiler', moc, parses the class declaration
  and produces a c++ implementation file from it, prefixed with "moc_".
  QMake handles the project and all complexity so that there is no difference
  for the developer.
 */
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
