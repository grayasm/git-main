********************************************************************************
                        Chapter 4. The Main Window
********************************************************************************

QMainWindow
-----------------------
Qt5 QMainWindow class   : http://doc.qt.io/qt-5/qmainwindow.html
Header                  : #include <QMainWindow>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Layout                  :
         +-----------------------------------+
         |           Menu Bar                |
         +-----------------------------------+
         |           Toolbars                |
         |   +---------------------------+   |
         |   |       Dock Widgets        |   |
         |   |   +-------------------+   |   |
         |   |   |                   |   |   |
         |   |   |   CentralWidget   |   |   |
         |   |   |                   |   |   |
         |   |   +-------------------+   |   |
         |   |                           |   |
         |   +---------------------------+   |
         |                                   |
         +-----------------------------------+
         | Status Bar                        |
         +-----------------------------------+

Code                    : setAttribute(Qt::WA_DeleteOnClose)
                          setWindowTitle("title")
                          QTextEdit* widget = new QTextEdit(this);
                          setCentralWidget(widget)
                          QAction* close=new QAction("&Close"), this);
                          QMenu* menu = menuBar()->addMenu("&File");
                          menu->addAction(close);


QIcon
-----------------------
Qt5 QIcon class         : http://doc.qt.io/qt-5/qicon.html
Header                  : #include <QIcon>
qmake                   : QT += gui
Inherits                :
Code                    : --current class is derived from QMainWindow--
                          QIcon icon(":/images/new.png");
                          QAction* action = new QAction(icon, "&New", parent);
                          action->setShortcut("Ctrl+N");
                          action->setStatusTip("Create a new document");
                          connect(action, SIGNAL(triggered()), this, SLOT(New));
                          QToolBar* toolbar = addToolBar("File");
                          toolbar->addAction(action);


QAction
-----------------------
Qt5 QAction class       : http://doc.qt.io/qt-5/qaction.html
Header                  : #include <QAction>
qmake                   : QT += widgets
Inherits                : QObject
Code                    :
                          --current class is derived from QMainWindow--
                          QIcon icon(":/images/cut.png");
                          QAction* action = new QAction(icon, "Cu&t", parent);
                          action->setShortcut("Ctrl+X");
                          action->setStatusTip("Cut");
                          action->setEnabled(false);
                          connect(textEditW, SIGNAL(copyAvailable(bool)),
                                  action,    SLOT(setEnabled(bool)));
                          connect(action,    SIGNAL(triggered()),
                                  textEditW, SLOT(cut()));
                          QMenu* menu = menuBar()->addMenu("&Edit");
                          menu->addAction(action);
                          QToolBar* toolbar = addToolBar("Edit");
                          toolbar->addAction(action);


QMenu
-----------------------
Qt5 QMenu class         : http://doc.qt.io/qt-5/qmenu.html
Header                  : #include <QMenu>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    :
                          --current class is derived from QMainWindow--
                          QMenu* menu = menuBar()->addMenu("&File");
                          menu->addAction(close);
                          menu->addSeparator();
                          menu->addAction(exit);


QMenuBar
-----------------------
Qt5 QMenuBar class      : http://doc.qt.io/qt-5/qmenubar.html
Header                  : #include <QMenuBar>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    :
                          --current class is derived from QMainWindow--
                          QMenuBar* menubar = menuBar();
                          QMenu* menu = menubar->addMenu("&File");
                          menu->addAction(close);
                          menu->addSeparator();
                          menu->addAction(exit);


QToolBar
-----------------------
Qt5 QToolBar class      : http://doc.qt.io/qt-5/qtoolbar.html
Header                  : #include <QToolBar>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    :
                          --current class is derived from QMainWindow--
                          QToolBar* toolbar = addToolBar("Edit");
                          toolbar->addAction(cut);
                          toolbar->addAction(copy);
                          toolbar->addAction(paste);

QStatusBar
-----------------------
Qt5 QStatusBar class    : http://doc.qt.io/qt-5/qstatusbar.html
Header                  : #include <QStatusBar>
qmake                   : QT += widgets
Inherits                : QWidgets -> QObject and QPaintDevice
Code                    :
                          --current class is derived from QMainWindow--
                          QStatusBar* statusbar = statusBar();
                          statusbar->showMessage("Ready");

QCloseEvent
-----------------------
Qt5 QCloseEvent class   : http://doc.qt.io/qt-5/qcloseevent.html
Header                  : #include <QCloseEvent>
qmake                   : QT += gui
Inherits                : QEvent
Code                    :
                          --current class is derived from QMainWindow--
                          void MdiWindow::closeEvent(QCloseEvent* event)
                          {
                            // class DocumentWindow : public QTextEdit;
                            mdiArea->closeAllSubWindows();
                            DocumentWindow* docwin =
                              qobject_cast<DocumentWindow*>(
                                 mdiArea->activeSubWindow());
                            if(docwin != NULL)
                              event->accept();
                            else
                              event->ignore();
                          }

QMdiArea
-----------------------
Qt5 QMdiArea class      : http://doc.qt.io/qt-5/qmdiarea.html
Header                  : #include <QMdiArea>
qmake                   : QT += widgets
Inherits                : QAbstractScrollArea -> QFrame -> QWidget ->
                                                        QObject and QPaintDevice
Code                    :
                          --current class is derived from QMainWindow--
                          setWindowTitle("MDI");
                          QMdiArea* mdiArea = new QMdiArea();
                          setCentralWidget( mdiArea );
                          connect(mdiArea,
                                  SIGNAL(subWindowActivated(QMdiSubWindow*)),
                                  this,
                                  SLOT(enableAction()));
                          QSignalMapper* mapper = new QSignalMapper(this);
                          connect(mapper,
                                  SIGNAL(mapped(QWidget*)),
                                  mdiArea,
                                  SLOT(setActiveSubWindow(QMdiSubWindow*)));

QMdiSubWindow
-----------------------
Qt5 QMdiSubWindow class : http://doc.qt.io/qt-5/qmdisubwindow.html
Header                  : #include <QMdiSubWindow>
qmake                   : QT += widgets
Inherits                : QWidgets -> QObject and QPaintDevice
Code                    :
                          QMdiArea mdiArea;
                          QMdiSubWindow* subWindow = new QMdiSubWindow;
                          subWindow->setWidget(internalWidget);
                          subWindow->setAttribute(Qt::WA_DeleteOnClose);
                          mdiArea.addSubWindow(subWindow);

QSignalMapper
-----------------------
Qt5 QSignalMapper class : http://doc.qt.io/qt-5/qsignalmapper.html
Header                  : #include <QSignalMapper>
qmake                   : QT += core
Inherits                : QObject
Code                    :

Please read the 4 samples 01_signal_trivial.cpp to 04_signal_mapper.cpp
Because it is not possible to connect correctly something like this:
connect(sender, SIGNAL(clicked()), receiver, SLOT(digitClicked(int)))
the class QSignalMapper is used to attach data to a widget that is transported
with the signal when emitted.
The code looks like this:

    QSignalMapper* mapper = new QSignalMapper(parent);
    connect(mapper, SIGNAL(mapped(int)), receiver, SLOT(function(int)));
    mapper->setMapping(sender, int_value);
    connect(sender, SIGNAL(signal()), mapper, SLOT(map()));

QSignalMapper can attach the following data to a signal:
  int, const QString&, QWidget* and QObject* types.


QDockWidget
-----------------------
Qt5 QDockWidget class   : http://doc.qt.io/qt-5/qdockwidget.html
Header                  : #include <QDockWidget>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    :
                          --current class is derived from QMainWindow--
                          QDockWidget* dock = new QDockWidget("Info", this);
                          QLabelDeriv* label = new QLabelDeriv(dock);
                          dock->setWidget(label);
                          addDockWidget(Qt::LeftDockWidgetArea, dock);
                          connect(textEdit->document(),
                                  SIGNAL(contentsChange(int, int, int)),
                                  label,
                                  SLOT(documentChanged(int, int, int)));

Resource File
-----------------------
Qt5 Resource System     : http://doc.qt.io/qt-5/resources.html

Resource Collection Files: .qrc
    <RCC>
        <qresource prefix="/">
            <file>images/copy.png</file>
        </qresource>
    </RCC>
    QIcon icon(":/images/copy.png");
    QIcon icon("qrc:///images/copy.png");

Accessing a resource by alias:
    <file alias="cut-img.png">images/cut.png</file>
    QIcon icon(":/cut-img.png");
