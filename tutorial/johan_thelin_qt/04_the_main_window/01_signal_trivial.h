#ifndef __signal_trivial_h__
#define __signal_trivial_h__


#include <QtWidgets/QtWidgets>


class Keypad : public QWidget
{
    Q_OBJECT
public:
    Keypad(QWidget* parent = 0);

signals:
    void digitCliked(int digit);

private slots:
    void bn0Clicked();
    void bn1Clicked();
    void bn2Clicked();
    void bn3Clicked();
    void bn4Clicked();
    void bn5Clicked();
    void bn6Clicked();
    void bn7Clicked();
    void bn8Clicked();
    void bn9Clicked();

private:
    QPushButton*    bn[10];
    QLineEdit*      line;
};

#endif // __signal_trivial_h__
