#ifndef __DocumentWindow_h__
#define __DocumentWindow_h__


#include <QtWidgets/QTextEdit>


class DocumentWindow : public QTextEdit
{
    Q_OBJECT

public:
    DocumentWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event);

private:
    bool isSafeToClose();
};

#endif // __DocumentWindow_h__
