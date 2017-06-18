/*
  QFileDialog::getOpenFileName

  To open a file, the static getOpenFileName method is used.

  The first argument accepted by the method is a parent for the dialog.
  The dialog is modal, so the given parent will be blocked from user
  interaction while it is open.

  The second argument is the caption of the window; the third is a path to
  the directory from which to start.
  The fourth and last argument is a list of filters separated by double
  semicolons (;;)

  The return value from the method is a QString. If the user has canceled or
  in other way aborted the dialog, the returned string is a null string.
  By using the isNull method, you can see whether the user picked a file.


  Build:
  qmake -project -nopwd $PWD/22_QFileDialog_open.cpp \
                        $PWD/22_QFileDialog_open.h \
                        -o 22_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 22_project.pro
  make
  ./22_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include "22_QFileDialog_open.h"



int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QVBoxLayout* layout = new QVBoxLayout(&dlg);
    QPushButton* open1 = new QPushButton("Open (single)");
    QPushButton* openx = new QPushButton("Open (multiple)");

    layout->addWidget(open1);
    layout->addWidget(openx);

    QTextEdit* txtedit = new QTextEdit();
    layout->addWidget(txtedit);

    Simple* simple = new Simple(&dlg);
    simple->m_edit = txtedit;

    QObject::connect(open1,                     // sender
                     SIGNAL(clicked()),     // signal
                     simple,                    // receiver
                     SLOT(open1_clicked()));    // slot

    QObject::connect(openx,                     // sender
                      SIGNAL(clicked()),    // signal
                      simple,                   // receiver
                      SLOT(openx_clicked()));   // slot

    dlg.show();
    return app.exec();
}


void Simple::open1_clicked()
{
    if(m_edit == 0)
        return;

    QString caption = "Open Document";
    QString filter  = "Document files (*.doc *.rtf);;All files(*.*)";

    QString filename = QFileDialog::getOpenFileName(
                NULL,                       // parent
                caption,                    // caption
                QDir::currentPath(),        // dir
                filter);                    // filter

    if (filename.isNull())
        return;

    m_edit->setText(filename);
}

void Simple::openx_clicked()
{
    if(m_edit == 0)
        return;

    QString caption = "Open Document(s)";
    QString filter  = "Document files (*.doc *.rtf);;All files(*.*)";

    QStringList filenames = QFileDialog::getOpenFileNames(
                NULL,                       // parent
                caption,                    // caption
                QDir::currentPath(),        // dir
                filter);                    // filter

    m_edit->clear();
    for(QStringList::iterator it = filenames.begin(); it != filenames.end(); it++)
        m_edit->append(*it);
}
