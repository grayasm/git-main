#include "MdiWindow.h"

MdiWindow::MdiWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MDI"));

    m_mdiArea = new QMdiArea();
    setCentralWidget(m_mdiArea);

    connect(m_mdiArea,                                      // sender
            SIGNAL(subWindowActivated(QMdiSubWindow *)),    // signal
            this,                                           // receiver
            SLOT(enableActions()));                         // slot

    m_mapper = new QSignalMapper(this);
    connect(m_mapper,                                       // sender
            SIGNAL(mapped(QWidget*)),                       // signal
            m_mdiArea,                                      // receiver
            SLOT(setActiveSubWindow(QMdiSubWindow*)));      // slot


    createActions();
    createMenus();
    createToolbars();
    statusBar()->showMessage(tr("Done"));

    enableActions();
}
