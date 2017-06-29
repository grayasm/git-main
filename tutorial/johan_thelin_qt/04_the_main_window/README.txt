********************************************************************************
                        Chapter 4. The Main Window
********************************************************************************

QMainWindow +
  setAttribute(Qt::WA_DeleteOnClose)
  setWindowTitle("title")
  setCentralWidget(widget)

QCloseEvent
    event->accept()
    event->ignore()

QIcon


QAction
    Action(QIcon("&Close"), parent);
    setShortcut("Ctrl+X");
    setStatusTip("Cut")
    setEnabled(false)

QMenu

QMenuBar
    menu = menuBar()->addMenu("&File")
    menu->addAction(actionNew)
    menu->addSeparator()

QToolBar
    toolbar = addToolBar("File")
    toolbar->addAction(actionNew)


QStatusBar
    statusbar = statusBar()
    statusbar->showMessage("Done")

QMdiArea
QMdiSubWindow


QSignalMapper


Resource File
    <RCC>
        <qresource prefix="/">
            <file>images/copy.png</file>
        </qresource>
    </RCC>

