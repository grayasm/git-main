#include <QtWidgets/QtWidgets>
#include "DocumentWindow.h"

DocumentWindow::DocumentWindow(QWidget* parent) : QTextEdit(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("%1[*]").arg("unnamed"));

    connect(document(),                             // sender
            SIGNAL(modificationChanged(bool)),      // signal
            this,                                   // receiver
            SLOT(setWindowModified(bool)));         // slot
}

void DocumentWindow::closeEvent(QCloseEvent *event)
{
    if(isSafeToClose())
        event->accept();
    else
        event->ignore();
}

bool DocumentWindow::isSafeToClose()
{
    if(document()->isModified())
    {
        switch(QMessageBox::warning(this,
                                    tr("MDI"),
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
