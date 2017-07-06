/*
  Source: https://doc.qt.io/archives/qq/qq10-signalmapper.html#thesubclassapproach

  We have here the same problem: make class Kaypad emit the signal
  "void digitClicked(int digit)" in the most efficient way.

  This sample uses a QPushButton derived class (e.g. KaypadButton) which knows
  upfront what number it has, so when clicked the following happens:
  a) the KeypadButton signal "void clicked()" is routed to "reemitClicked()"
  b) "reemitClicked()" slot emits KeypadButton signal "void clicked(int digit)"
  c) this signal is connected to class Keypad signal "void digitClicked(int)"

  IMPORTANT:
  This sample connects a SIGNAL TO ANOTHER SIGNAL!!
  In the book page 13 I learnt that we connect signals to slots. Now we see
  SIGNAL TO SIGNAL connection and it works.

  The drawback of this sample is the need to subclass QPushButton.


  build:
  qmake -project -nopwd $PWD/03_signal_subclass.cpp    \
                        $PWD/03_signal_subclass.h      \
                        -o 03_subclass.pro
  qmake -makefile -o Makefile "QT+=widgets" 03_subclass.pro
  make
  ./03_subclass
  git clean -f .
 */



#include "03_signal_subclass.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    Keypad* keypad = new Keypad(&dlg);

    dlg.show();
    return app.exec();
}

// ------------------------ KeypadButton ---------------------------------------
KeypadButton::KeypadButton(int digit, QWidget* parent) : QPushButton(parent)
{
    m_digit = digit;
    QString text = QString::number(m_digit);
    setText(text);
    connect(this, SIGNAL(clicked()), this, SLOT(reeemitClicked()));
}

void KeypadButton::reeemitClicked()
{
    emit clicked(m_digit);
}

// --------------------------- Keypad ------------------------------------------
Keypad::Keypad(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(parent);

    for(int i = 0; i < 10; ++i)
    {
        bn[i] = new KeypadButton(i, this);
        connect(bn[i], SIGNAL(clicked(int)), this, SIGNAL(digitCliked(int)));
    }

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

    // this is added to show feedback in the dialog
    connect(this, SIGNAL(digitCliked(int)), this, SLOT(bnClicked(int)));
}

void Keypad::bnClicked(int digit)
{
    QString str = "Keypad ";
    str += QString::number(digit);
    str += " clicked";
    line->setText(str);
}
