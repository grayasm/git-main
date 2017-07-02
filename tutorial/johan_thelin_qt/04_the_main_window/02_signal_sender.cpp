/*
  Source: https://doc.qt.io/archives/qq/qq10-signalmapper.html#thesenderapproach

  The Keypad problem explained in signal_trivial remains here too, which is
  to emit a signal: "void digitClicked(int digit)" in the most efficient way.

  In this sample we gother all bnNClicked() slots into one private slot
  "void bnClicked()" which will do the following:
  a) call QObject::sender() to retrieve the QObject* of the sender widget
  b) cast it to QPushButton*
  c) get the text of the button and assume it's one of "0", "1", .. "9"
  d) convert to digit and finally "emit digitClicked(digit)"

  The drawback is that if we replace the QPushButton with another type of
  widget and forget to change the case, then will get a crash. Similarly,
  if we change the text of the buttons ("NIL" istead of "0")
  the digitClicked(int) signal will be emitted with an incorrect value.

  build:
  qmake -project -nopwd $PWD/02_signal_sender.cpp    \
                        $PWD/02_signal_sender.h      \
                        -o 02_sender.pro
  qmake -makefile -o Makefile "QT+=widgets" 02_sender.pro
  make
  ./02_sender
  git clean -f .
 */


#include "02_signal_sender.h"


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

    for(int i = 0; i < 10; ++i)
    {
        QString text = QString::number(i);
        bn[i] = new QPushButton(text, this);
        connect(bn[i], SIGNAL(clicked()), this, SLOT(bnClicked()));
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
}

void Keypad::bnClicked()
{
	QPushButton* bn = (QPushButton*) sender();
    QString text = bn->text();
    QCharRef ch = text[0];
    int num = ch.digitValue();

    QString str = "Keypad ";
    str += ch;
    str += " clicked";
    line->setText(str);

    emit digitCliked(num);
}
