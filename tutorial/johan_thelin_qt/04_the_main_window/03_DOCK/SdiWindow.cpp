#include "SdiWindow.h"
#include "InfoWidget.h"



SdiWindow::SdiWindow(QWidget *parent) : QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("%1[*] - %2").arg(tr("unnamed").arg(tr("SDI"))));

    m_docWidget = new QTextEdit(this);
    setCentralWidget(m_docWidget);

    connect(m_docWidget->document(),                // sender
            SIGNAL(modificationChanged(bool)),      // signal
            this,                                   // receiver
            SLOT(setWindowModified(bool)));         // slot

    createDocks();
    createActions();
    createMenus();
    createToolbars();

    statusBar()->showMessage(tr("Done"));
}

void SdiWindow::createDocks()
{
    m_dock = new QDockWidget(tr("Information"), this);
    InfoWidget* info = new InfoWidget(m_dock);
    m_dock->setWidget(info);
    addDockWidget(Qt::LeftDockWidgetArea, m_dock);

    connect(m_docWidget->document(),
            SIGNAL(contentsChange(int, int, int)),
            info,
            SLOT(documentChanged(int,int,int)));
}

void SdiWindow::closeEvent(QCloseEvent* event)
{
    if(isSafeToClose())
        event->accept();
    else
        event->ignore();
}

bool SdiWindow::isSafeToClose()
{
    if(isWindowModified())
    {
        switch(QMessageBox::warning(this, tr("SDI"),
                                    tr("The document has unsaved changes.\n"
                                       "Do you want to save it before it is"
                                       "closed?"),
                                    QMessageBox::Discard | QMessageBox::Cancel))
        {
        case QMessageBox::Cancel:
            return false;
        default:
            return true;
        }
    }
    return true;
}

void SdiWindow::fileNew()
{
    (new SdiWindow())->show();
}

void SdiWindow::helpAbout()
{
    QMessageBox::about(this,
                       tr("About SDI"),
                       tr("A single document interface application."));
}

void SdiWindow::createActions()
{
    // New, Close, Exit
    m_actionNew = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    m_actionNew->setShortcut(tr("Ctrl+N"));
    m_actionNew->setStatusTip(tr("Create a new document"));
    connect(m_actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));

    m_actionClose = new QAction(tr("&Close"), this);
    m_actionClose->setShortcut(tr("Ctrl+W"));
    m_actionClose->setStatusTip(tr("Close this document"));
    connect(m_actionClose, SIGNAL(triggered()), this, SLOT(close()));

    m_actionExit = new QAction(tr("E&xit"), this);
    m_actionExit->setShortcut(tr("Ctrl+Q"));
    m_actionExit->setStatusTip(tr("Quit the application"));
    connect(m_actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));


    // Cut, Copy, Paste
    m_actionCut = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    m_actionCut->setShortcut(tr("Ctrl+X"));
    m_actionCut->setStatusTip(tr("Cut"));
    m_actionCut->setEnabled(false);
    connect(m_docWidget, SIGNAL(copyAvailable(bool)), // to enable cut icon
            m_actionCut, SLOT(setEnabled(bool)));
    connect(m_actionCut, SIGNAL(triggered()), m_docWidget, SLOT(cut())); //cut


    m_actionCopy = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    m_actionCopy->setShortcut(tr("Ctrl+C"));
    m_actionCopy->setStatusTip(tr("Copy"));
    m_actionCopy->setEnabled(false);
    connect(m_docWidget, SIGNAL(copyAvailable(bool)), // to enable copy icon
            m_actionCopy, SLOT(setEnabled(bool)));
    connect(m_actionCopy, SIGNAL(triggered()), m_docWidget, SLOT(copy()));


    m_actionPaste = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    m_actionPaste->setShortcut(tr("Ctrl+V"));
    m_actionPaste->setStatusTip(tr("Paste"));
    connect(m_actionPaste, SIGNAL(triggered()), m_docWidget, SLOT(paste()));


    // About, AboutQt
    m_actionAbout = new QAction(tr("&About"), this);
    m_actionAbout->setStatusTip(tr("About this application"));
    connect(m_actionAbout, SIGNAL(triggered(bool)), this, SLOT(helpAbout()));

    m_actionAboutQt = new QAction(tr("About &Qt"), this);
    m_actionAboutQt->setStatusTip(tr("About the Qt toolkit"));
    connect(m_actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void SdiWindow::createMenus()
{
    QMenu* menu;

    menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(m_actionNew);
    menu->addAction(m_actionClose);
    menu->addSeparator();
    menu->addAction(m_actionExit);

    menu = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(m_actionCut);
    menu->addAction(m_actionCopy);
    menu->addAction(m_actionPaste);

    menu = menuBar()->addMenu(tr("&View"));
    menu->addAction(m_dock->toggleViewAction());

    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(m_actionAbout);
    menu->addAction(m_actionAboutQt);
}

void SdiWindow::createToolbars()
{
    QToolBar* toolbar;

    toolbar = addToolBar(tr("File"));
    toolbar->addAction(m_actionNew);

    toolbar = addToolBar(tr("Edit"));
    toolbar->addAction(m_actionCut);
    toolbar->addAction(m_actionCopy);
    toolbar->addAction(m_actionPaste);
}
