/*
  QFileDialog::getSaveFileName

  The QFileDialog class has a method for asking for a file name when saving
  files: getSaveFileName. If the file already exists, a warning dialog is shown.
  When specifying filters, it is good to know that Qt helps to enforce the
  file extension if not specified by the user. This means that you need an
  All files (*.*) filter to enable the user to pick a file extension freely.

  qmake -project -nopwd $PWD/23_QFileDialog_save.h \
                        $PWD/23_QFileDialog_save.cpp \
                        -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
 */


#include <QtWidgets/QtWidgets>
#include "23_QFileDialog_save.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QVBoxLayout* layout = new QVBoxLayout(&dlg);
    QPushButton* save = new QPushButton("Save text");
    QTextEdit* edit = new QTextEdit();

    layout->addWidget(save);
    layout->addWidget(edit);

    Simple* simple = new Simple(&dlg);
    simple->m_edit = edit;

    QObject::connect(save,                  // sender
                     SIGNAL(clicked()),     // signal
                     simple,                // receiver
                     SLOT(saveText()));     // slot

    dlg.show();

    return app.exec();
}



void Simple::saveText()
{
    if (m_edit == NULL)
        return;

    QString caption = "Save Document";
    QString filter  = "Document files (*.doc *.rtf);;All files(*.*)";

    QString filename = QFileDialog::getSaveFileName(
                NULL,                       // parent
                caption,                    // caption
                QDir::currentPath(),        // dir
                filter);                    // filter

    if (filename.isNull())
        return;


    if (!filename.isNull())
        m_edit->setText(filename);
}
