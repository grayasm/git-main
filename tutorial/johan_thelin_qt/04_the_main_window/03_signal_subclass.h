#ifndef __signal_subclass_h__
#define __signal_subclass_h__

#include <QtWidgets/QtWidgets>


class KeypadButton : public QPushButton
{
    Q_OBJECT
public:
    KeypadButton(int digit, QWidget* parent);

signals:
    void clicked(int digit);

private slots:
    void reeemitClicked();

private:
    int m_digit;
};


class Keypad : public QWidget
{
    Q_OBJECT
public:
    Keypad(QWidget* parent = 0);

signals:
    void digitCliked(int digit);

private slots:
    void bnClicked(int digit);

private:
    KeypadButton*   bn[10];
    QLineEdit*      line;
};




#endif // __signal_subclass_h__
