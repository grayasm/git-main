#include <QObject>
#include <QtWidgets/QTextEdit>

class Simple : public QObject
{
    Q_OBJECT

public:
    Simple(QObject* parent) : QObject(parent), m_edit(0) {}
    ~Simple() {}

public slots:
    void openDir();

public:
    QTextEdit* m_edit;
};
