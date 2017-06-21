
#include <QtWidgets/QtWidgets>

class SdiWindow : public QMainWindow
{
    Q_OBJECT

public:
    SdiWindow(QWidget* parent);


private:
    void createActions();
    void createMenus();
    void createToolbars();

private:
    QTextEdit*  m_docWidget;
};
