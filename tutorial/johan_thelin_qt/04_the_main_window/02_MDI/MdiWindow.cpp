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
    connect(m_mapper,
            SIGNAL(mapped(QWidget*)),
            m_mdiArea,
            SLOT(setActiveSubWindow(QMdiSubWindow*)));


    createActions();
    createMenus();
    createToolbars();
    statusBar()->showMessage(tr("Done"));

    enableActions();
}

void MdiWindow::closeEvent(QCloseEvent *event)
{
    m_mdiArea->closeAllSubWindows();

    if(activeDocument() != NULL)
        event->accept();
    else
        event->ignore();
}

void MdiWindow::fileNew()
{
    DocumentWindow* document = new DocumentWindow();
    m_mdiArea->addSubWindow(document);

    connect(document,                       // sender
            SIGNAL(copyAvailable(bool)),    // signal
            m_actionCut,                    // receiver
            SLOT(setEnabled(bool)));        // slot

    connect(document,
            SIGNAL(copyAvailable(bool)),
            m_actionCopy,
            SLOT(setEnabled(bool)));

    document->show();
}

void MdiWindow::helpAbout()
{
    QMessageBox::about(this,
                       tr("About MDI"),
                       tr("A multiple document interface application."));
}


DocumentWindow* MdiWindow::activeDocument()
{
    return qobject_cast<DocumentWindow*>(m_mdiArea->activeSubWindow());
}

void MdiWindow::enableActions()
{
    bool hasDocuments = (activeDocument() != 0);

    m_actionClose->setEnabled(hasDocuments);
    m_actionPaste->setEnabled(hasDocuments);

    m_actionTile->setEnabled(hasDocuments);
    m_actionCascade->setEnabled(hasDocuments);
    m_actionNext->setEnabled(hasDocuments);
    m_actionPrevious->setEnabled(hasDocuments);
    m_actionSeparator->setEnabled(hasDocuments);

    bool hasSelection =
            hasDocuments && activeDocument()->textCursor().hasSelection();

    m_actionCut->setEnabled(hasSelection);
    m_actionCopy->setEnabled(hasSelection);
}

void MdiWindow::createActions()
{
    // New, Close, Exit
    m_actionNew = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    m_actionNew->setShortcut(tr("Ctrl+N"));
    m_actionNew->setStatusTip(tr("Create a new document"));
    connect(m_actionNew,
            SIGNAL(triggered(bool)),
            this,
            SLOT(fileNew()));

    m_actionClose = new QAction(tr("&Close"), this);
    m_actionClose->setShortcut(tr("Ctrl+W"));
    m_actionClose->setStatusTip(tr("Close this document"));
    connect(m_actionClose,
            SIGNAL(triggered(bool)),
            m_mdiArea,
            SLOT(closeActiveSubWindow()));

    m_actionExit = new QAction(tr("E&xit"), this);
    m_actionExit->setShortcut(tr("Ctrl+Q"));
    m_actionExit->setStatusTip(tr("Quit the application"));
    connect(m_actionExit,
            SIGNAL(triggered(bool)),
            qApp,
            SLOT(closeAllWindows()));


    // Cut, Copy, Paste
    m_actionCut = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    m_actionCut->setShortcut(tr("Ctrl+X"));
    m_actionCut->setStatusTip(tr("Cut"));
    m_actionCut->setEnabled(false);
    connect(m_actionCut,
            SIGNAL(triggered(bool)),
            this,
            SLOT(editCut()));

    m_actionCopy = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    m_actionCopy->setShortcut(tr("Ctrl+C"));
    m_actionCopy->setStatusTip(tr("Copy"));
    m_actionCopy->setEnabled(false);
    connect(m_actionCopy,
            SIGNAL(triggered(bool)),
            this,
            SLOT(editCopy));

    m_actionPaste = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    m_actionPaste->setShortcut(tr("Ctrl+V"));
    m_actionPaste->setStatusTip(tr("Paste"));
    connect(m_actionPaste,
            SIGNAL(triggered(bool)),
            this,
            SLOT(editPaste()));


    // Tile, Cascase, Next, Previous
    m_actionTile = new QAction(tr("&Tile"), this);
    m_actionTile->setStatusTip(tr("Tile the windows"));
    connect(m_actionTile,
            SIGNAL(triggered(bool)),
            m_mdiArea,
            SLOT(tileSubWindows()));

    m_actionCascade = new QAction(tr("&Cascade"), this);
    m_actionCascade->setStatusTip(tr("Cascade the windows"));
    connect(m_actionCascade,
            SIGNAL(triggered(bool)),
            m_mdiArea,
            SLOT(cascadeSubWindows()));

    m_actionNext = new QAction(tr("&Next window"), this);
    m_actionNext->setStatusTip(tr("Move to the next window"));
    connect(m_actionNext,
            SIGNAL(triggered(bool)),
            m_mdiArea,
            SLOT(activateNextSubWindow()));

    m_actionPrevious = new QAction(tr("&Previous window"), this);
    m_actionPrevious->setStatusTip(tr("Move to the previous window"));
    connect(m_actionPrevious,
            SIGNAL(triggered(bool)),
            m_mdiArea,
            SLOT(activatePreviousSubWindow()));


    // Separator, About, AboutQt
    m_actionSeparator = new QAction(this);
    m_actionSeparator->setSeparator(true);

    m_actionAbout = new QAction(tr("&About"), this);
    m_actionAbout->setStatusTip(tr("About this application"));
    connect(m_actionAbout,
            SIGNAL(triggered(bool)),
            this,
            SLOT(helpAbout()));


    m_actionAboutQt = new QAction(tr("About &Qt"), this);
    m_actionAboutQt->setStatusTip(tr("About the Qt toolkit"));
    connect(m_actionAboutQt,
            SIGNAL(triggered(bool)),
            qApp,
            SLOT(aboutQt()));
}

void MdiWindow::createMenus()
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

    m_menuWindow = menuBar()->addMenu(tr("&Window"));
    connect(m_menuWindow,
            SIGNAL(aboutToShow()),
            this,
            SLOT(updateWindowList()));


    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(m_actionAbout);
    menu->addAction(m_actionAboutQt);
}

void MdiWindow::createToolbars()
{
    QToolBar* toolbar;

    toolbar = addToolBar(tr("File"));
    toolbar->addAction(m_actionNew);

    toolbar = addToolBar(tr("Edit"));
    toolbar->addAction(m_actionCut);
    toolbar->addAction(m_actionCopy);
    toolbar->addAction(m_actionPaste);
}

void MdiWindow::editCut()
{
    activeDocument()->cut();
}

void MdiWindow::editCopy()
{
    activeDocument()->copy();
}

void MdiWindow::editPaste()
{
    activeDocument()->paste();
}

void MdiWindow::updateWindowList()
{
    m_menuWindow->clear();

    m_menuWindow->addAction(m_actionTile);
    m_menuWindow->addAction(m_actionCascade);
    m_menuWindow->addSeparator();
    m_menuWindow->addAction(m_actionNext);
    m_menuWindow->addAction(m_actionPrevious);
    m_menuWindow->addAction(m_actionSeparator);


    int i = 1;
    foreach(QWidget* w, m_mdiArea->subWindowList())
    {
        QString text;
        if(i < 10)
            text = tr("&%1 %2").arg(i++).arg(w->windowTitle());
        else
            text = w->windowTitle();

        QAction* action = m_menuWindow->addAction(text);
        action->setCheckable(true);
        action->setChecked(w == activeDocument());

        connect(action,
                SIGNAL(triggered(bool)),
                m_mapper,
                SLOT(map()));
        m_mapper->setMapping(action, w);
    }
}













