/*
  Opening Directories, QFileDialog::getExistingDirectory

  Slightly less common than asking for a file name is asking for a directory,
  but the QFileDialog class has a static member for this as well:

  getExistingDirectory.

  The arguments are the same as for the methods for opening and saving files,
  except that no filter is given because there is no point to filtering for
  extensions when working with directories.

  Build:
  qmake -project -nopwd $PWD/24_QFileDialog_opendir.h \
                        $PWD/24_QFileDialog_opendir.cpp \
                        -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
 */


#include <QtWidgets/QtWidgets>
#include "24_QFileDialog_opendir.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QVBoxLayout* layout = new QVBoxLayout(&dlg);
    QPushButton* open = new QPushButton("Open Directory");
    QTextEdit* edit = new QTextEdit();

    layout->addWidget(open);
    layout->addWidget(edit);

    Simple* simple = new Simple(&dlg);
    simple->m_edit = edit;

    QObject::connect(open,                      // sender
                     SIGNAL(clicked(bool)),     // signal
                     simple,                    // receiver
                     SLOT(openDir()));          // slot

    dlg.show();
    return app.exec();
}


void Simple::openDir()
{
    if(m_edit == NULL) return;

    QString dirname = QFileDialog::getExistingDirectory(
                NULL,                       // parent
                tr("Select a Directory"),   // caption
                QDir::currentPath());       // directory

    if(dirname.isNull())
        return;

    m_edit->setText(dirname);
}
