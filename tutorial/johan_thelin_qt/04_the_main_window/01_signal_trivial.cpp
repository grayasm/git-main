/*
  Source: https://doc.qt.io/archives/qq/qq10-signalmapper.html#thetrivialsolution

  We want this Keypad component to emit a signal with the sender
  (the clicked button) number as an int parameter, like "void clicked(int)".

  However, the QPushButton class has not signals and its base class
  QAbstractButton defines this:

Q_SIGNALS:
    void pressed();
    void released();
    void clicked(bool checked = false);
    void toggled(bool checked);

  So, there is no way to tell which number(button) has sent the signal to a slot
  so that we can emit "void clicked(int)" in that slot.
  The only way to solve it is to connect EACH button invidually to a DISTINCT
  slot, and this copy/paste is almost UNBEARABLE. (as by the author)

  build:
  qmake -project -nopwd $PWD/01_signal_trivial.cpp    \
                        $PWD/01_signal_trivial.h      \
                        -o 01_trivial.pro
  qmake -makefile -o Makefile "QT+=widgets" 01_trivial.pro
  make
  ./01_trivial
  git clean -f .
 */



#include "01_signal_trivial.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    Keypad* keypad = new Keypad(&dlg);

    dlg.show();
    return app.exec();
}


Keypad::Keypad(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(parent);

    bn[1] = new QPushButton("1");
    bn[2] = new QPushButton("2");
    bn[3] = new QPushButton("3");
    bn[4] = new QPushButton("4");
    bn[5] = new QPushButton("5");
    bn[6] = new QPushButton("6");
    bn[7] = new QPushButton("7");
    bn[8] = new QPushButton("8");
    bn[9] = new QPushButton("9");
    bn[0] = new QPushButton("0");


    layout->addWidget(bn[1], 0, 0);
    layout->addWidget(bn[2], 0, 1);
    layout->addWidget(bn[3], 0, 2);
    layout->addWidget(bn[4], 1, 0);
    layout->addWidget(bn[5], 1, 1);
    layout->addWidget(bn[6], 1, 2);
    layout->addWidget(bn[7], 2, 0);
    layout->addWidget(bn[8], 2, 1);
    layout->addWidget(bn[9], 2, 2);
    layout->addWidget(bn[0], 3, 1);

    line = new QLineEdit();
    layout->addWidget(line, 4, 0, 1, 3);

    connect(bn[0], SIGNAL(clicked()), this, SLOT(bn0Clicked()));
    connect(bn[1], SIGNAL(clicked()), this, SLOT(bn1Clicked()));
    connect(bn[2], SIGNAL(clicked()), this, SLOT(bn2Clicked()));
    connect(bn[3], SIGNAL(clicked()), this, SLOT(bn3Clicked()));
    connect(bn[4], SIGNAL(clicked()), this, SLOT(bn4Clicked()));
    connect(bn[5], SIGNAL(clicked()), this, SLOT(bn5Clicked()));
    connect(bn[6], SIGNAL(clicked()), this, SLOT(bn6Clicked()));
    connect(bn[7], SIGNAL(clicked()), this, SLOT(bn7Clicked()));
    connect(bn[8], SIGNAL(clicked()), this, SLOT(bn8Clicked()));
    connect(bn[9], SIGNAL(clicked()), this, SLOT(bn9Clicked()));
}

/*  These slots emit digitClicked(int) for integrators, which was requested
 *  in the beginning.
 */
void Keypad::bn0Clicked()
{
    line->setText("keypad 0 clicked");
    emit digitCliked(0);
}
void Keypad::bn1Clicked()
{
    line->setText("keypad 1 clicked");
    emit digitCliked(1);
}
void Keypad::bn2Clicked()
{
    line->setText("keypad 2 clicked");
    emit digitCliked(2);
}
void Keypad::bn3Clicked()
{
    line->setText("keypad 3 clicked");
    emit digitCliked(3);
}
void Keypad::bn4Clicked()
{
    line->setText("keypad 4 clicked");
    emit digitCliked(4);
}
void Keypad::bn5Clicked()
{
    line->setText("keypad 5 clicked");
    emit digitCliked(5);
}
void Keypad::bn6Clicked()
{
    line->setText("keypad 6 clicked");
    emit digitCliked(6);
}
void Keypad::bn7Clicked()
{
    line->setText("keypad 7 clicked");
    emit digitCliked(7);
}
void Keypad::bn8Clicked()
{
    line->setText("keypad 8 clicked");
    emit digitCliked(8);
}
void Keypad::bn9Clicked()
{
    line->setText("keypad 9 clicked");
    emit digitCliked(9);
}
