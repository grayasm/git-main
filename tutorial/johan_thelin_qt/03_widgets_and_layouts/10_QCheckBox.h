#include <QObject>
#include <QtWidgets/QLabel>

class Simple : public QObject
{
    Q_OBJECT
public:
    Simple(QObject* parent) : QObject(parent){}

public slots:
    void setChanged(int);

public:
    QLabel* label;
};
