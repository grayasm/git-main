/*
  Source: https://doc.qt.io/archives/qq/qq10-signalmapper.html#thesignalmapperapproach

  So, the problem is still the same, make Keypad emit "void digitClicked(int)"
  signal in some efficient way, without a lot of code, or potential bugs.

  This sample shows the most effective way to connect signal
  "void QAbstractButton::clicked()" to another signal
  "void Keypad::digitClicked(int digit)" with the help of QSignalMapper.

  QSignalMapper can attach an "int", "QString", "QWidget*" or "QObject*" data
  as extra information to a simple signal "void clicked(void)" and transport
  it to the destination slot or signal matched by type : void SlotFn(int);
  void SlotFn(const QString&); void SlotFn(QWidget*); void SlotFn(QObject*);

class QSignalMapper:
    void setMapping(QObject *sender, int id);
    void setMapping(QObject *sender, const QString &text);
    void setMapping(QObject *sender, QWidget *widget);
    void setMapping(QObject *sender, QObject *object);

    QObject *mapping(int id) const;
    QObject *mapping(const QString &text) const;
    QObject *mapping(QWidget *widget) const;
    QObject *mapping(QObject *object) const;

Q_SIGNALS:
    void mapped(int);
    void mapped(const QString &);
    void mapped(QWidget *);
    void mapped(QObject *);


  build:
  qmake -project -nopwd $PWD/04_signal_mapper.cpp    \
                        $PWD/04_signal_mapper.h      \
                        -o 04_mapper.pro
  qmake -makefile -o Makefile "QT+=widgets" 04_mapper.pro
  make
  ./04_mapper
  git clean -f .
 */


#include "04_signal_mapper.h"


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
    // Required to use the mapper:
    // (1) create the mapper
    QSignalMapper* mapper = new QSignalMapper(this);
    // (2) connect the INT mapper to destination SLOT or SIGNAL
    connect(mapper, SIGNAL(mapped(int)), this, SIGNAL(digitCliked(int)));

    for(int i = 0; i < 10; ++i)
    {
        QString text = QString::number(i);
        bn[i] = new QPushButton(text, this);

        // (3) set info data to be transported with the signal
        mapper->setMapping(bn[i], i);
        // (4) connect the sender-SIGNAL to the mapper
        connect(bn[i], SIGNAL(clicked()), mapper, SLOT(map()));
    }

    QGridLayout* layout = new QGridLayout(parent);
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

    // added this for feedback in the dialog
    connect(this, SIGNAL(digitCliked(int)), this, SLOT(bnClicked(int)));
}

void Keypad::bnClicked(int digit)
{
    QString str = "Keypad ";
    str += QString::number(digit);
    str += " clicked";
    line->setText(str);
}
