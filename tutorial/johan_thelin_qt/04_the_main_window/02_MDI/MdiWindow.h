#ifndef __MdiWindow_h__
#define __MdiWindow_h__


#include <QtWidgets/QtWidgets>
#include "DocumentWindow.h"


class MdiWindow : public QMainWindow
{
    Q_OBJECT

public:
    MdiWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void fileNew();

    void editCut();
    void editCopy();
    void editPaste();

    void helpAbout();

    void enableActions();
    void updateWindowList();

private:
    void createActions();
    void createMenus();
    void createToolbars();

    DocumentWindow* activeDocument();

    QMdiArea*           m_mdiArea;
    QSignalMapper*      m_mapper;
    QMenu*              m_menuWindow;

    QAction*            m_actionNew;
    QAction*            m_actionClose;
    QAction*            m_actionExit;

    QAction*            m_actionCut;
    QAction*            m_actionCopy;
    QAction*            m_actionPaste;

    QAction*            m_actionTile;
    QAction*            m_actionCascade;
    QAction*            m_actionNext;
    QAction*            m_actionPrevious;
    QAction*            m_actionSeparator;

    QAction*            m_actionAbout;
    QAction*            m_actionAboutQt;
};



#endif // __MdiWindow_h__
