#include <QObject>
#include <QtWidgets/QListWidget>

class Simple : public QObject
{
    Q_OBJECT

public:
    Simple(QObject* parent);

public slots:
    void moveLeft();
    void moveRight();

public:
    QListWidget* leftList;
    QListWidget* rightList;
};
