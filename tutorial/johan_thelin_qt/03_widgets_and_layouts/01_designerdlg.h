#ifndef __01_DESIGNERDLG_H__
#define __01_DESIGNERDLG_H__

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

#endif // __01_DESIGNERDLG_H__
