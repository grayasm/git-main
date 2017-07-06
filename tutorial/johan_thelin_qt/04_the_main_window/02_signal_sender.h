#ifndef __signal_sender_h__
#define __signal_sender_h__


#include <QtWidgets/QtWidgets>


class Keypad : public QWidget
{
    Q_OBJECT
public:
    Keypad(QWidget* parent = 0);

signals:
    void digitCliked(int digit);

private slots:
    void bnClicked();

private:
    QPushButton*    bn[10];
    QLineEdit*      line;
};

#endif // __signal_sender_h__
