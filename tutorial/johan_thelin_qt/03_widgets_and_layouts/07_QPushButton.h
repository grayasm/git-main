/*
  In this example we have 2 buttons that needs to be connected to 2 slots.
  The purpose of class Simple is to have 2 slots that we can connect to.

  I looked up the prototype of Object::connect, and it requires 2 Object* types.
  template<Func1, Func2>
  QObject::connect(Object*, Func1, Object*, Func2);

  To make this connect work:
  QObject::connect(button, SIGNAL(clicked()), simple, SLOT(buttonClicked()));
  it is needed that "simple" (the receiver) to be derived from QObject.

  If it derives from QObject it also needs Q_OBJECT macro,
  so it must be in a header because Qt5 moc tool parses header files only.
 */

#include <QObject>

class Simple : public QObject
{
    Q_OBJECT

public:
    Simple(QObject* parent) : QObject(parent){}

public slots:
    void buttonClicked();
    void buttonToggled();
};
