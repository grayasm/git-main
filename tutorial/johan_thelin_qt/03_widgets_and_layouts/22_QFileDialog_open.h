#include <QObject>
#include <QtWidgets/QTextEdit>



class Simple : public QObject
{
    Q_OBJECT

public:
    Simple(QObject* parent) : QObject(parent), m_edit(0) {}
    ~Simple(){}


signals:

public slots:
    void open1_clicked();
    void openx_clicked();

public:
    QTextEdit*  m_edit;
};
