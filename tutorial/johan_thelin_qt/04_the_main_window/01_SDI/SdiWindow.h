#ifndef __SdiWindow_h__
#define __SdiWindow_h__

#include <QtWidgets/QtWidgets>

class SdiWindow : public QMainWindow
{
    Q_OBJECT

public:
    SdiWindow(QWidget* parent);

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void fileNew();
    void helpAbout();

private:
    void createActions();
    void createMenus();
    void createToolbars();
    bool isSafeToClose();

private:
    QTextEdit*  m_docWidget;

    QAction*    m_actionNew;
    QAction*    m_actionClose;
    QAction*    m_actionExit;

    QAction*    m_actionCut;
    QAction*    m_actionCopy;
    QAction*    m_actionPaste;

    QAction*    m_actionAbout;
    QAction*    m_actionAboutQt;
};


#endif // __SdiWindow_h__
