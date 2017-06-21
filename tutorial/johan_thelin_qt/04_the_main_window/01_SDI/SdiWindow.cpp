/*

  Build:
  qmake -project -nopwd $PWD/SdiWindow.cpp   \
                        $PWD/SdiWindow.h     \
                        -o 01_project.pro
  qmake -makefile -o Makefile "QT += widgets" 01_project.pro
  make
  ./01_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include "01_SdiWindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    SdiWindow* win = new SdiWindow(0);
    win->show();

    return app.exec();
}


SdiWindow::SdiWindow(QWidget *parent) : QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("%1[*] - %2").arg("unnamed").arg("SDI"));

    m_docWidget = new QTextEdit(this);
    setCentralWidget(m_docWidget);

    QObject::connect(m_docWidget->document(),           // sender
                     SIGNAL(modificationChanged(bool)), // signal
                     this,                              // receiver
                     SLOT(setWindowModified(bool)));    // slot

    createActions();
    createMenus();
    createToolbars();

    statusBar()->showMessage("Done");
}

void SdiWindow::createActions()
{

}

void SdiWindow::createMenus()
{

}

void SdiWindow::createToolbars()
{

}
