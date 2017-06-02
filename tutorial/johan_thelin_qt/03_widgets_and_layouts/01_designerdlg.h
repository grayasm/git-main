#ifndef _DESIGNERDLG_H
#define _DESIGNERDLG_H

#include <QDialog>

namespace Ui {
class DesignerDlg;
}

class DesignerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit DesignerDlg(QWidget *parent = 0);
    ~DesignerDlg();

private:
    Ui::DesignerDlg *ui;
};

#endif // _DESIGNERDLG_H
