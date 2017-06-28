#ifndef __SdiWindow_h__
#define __SdiWindow_h__


#include <QtWidgets/QtWidgets>


class SdiWindow : public QMainWindow
{
    Q_OBJECT

public:
    SdiWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void fileNew();
    void helpAbout();

private:
    void createDocks();
    void createActions();
    void createMenus();
    void createToolbars();

    bool isSafeToClose();

    QDockWidget*    m_dock;
    QTextEdit*      m_docWidget;

    QAction*        m_actionNew;
    QAction*        m_actionClose;
    QAction*        m_actionExit;

    QAction*        m_actionCut;
    QAction*        m_actionCopy;
    QAction*        m_actionPaste;

    QAction*        m_actionAbout;
    QAction*        m_actionAboutQt;
};

#endif // __SdiWindow_h__
