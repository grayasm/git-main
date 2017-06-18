********************************************************************************
                        Chapter 3. Widgets and Layouts
********************************************************************************
1. Qt5 classes hierarchy
------------------------

   http://doc.qt.io/qt-5/hierarchy.html


2. Qt Widget classes
--------------------
Qt5 widgets classes     : http://doc.qt.io/qt-5/qtwidgets-module.html


QHBoxLayout
--------------------
Qt5 QHBoxLayout class   : http://doc.qt.io/qt-5/qhboxlayout.html
Header                  : #include <QHBoxLayout>
qmake                   : QT += widgets
Inherits                : QBoxLayout -> QLayout -> QObject and QLayoutItem
Code                    : QHBoxLayout* layout = new QHBoxLayout(&dlg);
                          layout->addWidget(button1);

QVBoxLayout
--------------------
Qt5 QVBoxLayout class   : http://doc.qt.io/qt-5/qvboxlayout.html
Header                  : #include <QVBoxLayout>
qmake                   : QT += widgets
Inherits                : QBoxLayout -> QLayout -> QObject and QLayoutItem
Code                    : QVBoxLayot* layout = new QVBoxLayout(&dlg);
                          layout->addWidget(button1);

QGridLayout
--------------------
Qt5 QGridLayout class   : http://doc.qt.io/qt-5/qgridlayout.html
Header                  : #include <QGridLayout>
qmake                   : QT += widgets
Inherits                : QLayout -> QObject and QLayoutItem
Code                    : QGridLayout* layout = new QGridLayout(&dlg);
                          // add at: row, col, rowspan, colspan
                          layout->addWidget(button1, 0, 0, 1, 2);

QPushButton
--------------------
Qt5 QPushButton class   : http://doc.qt.io/qt-5/qpushbutton.html
Header                  : #include <QPushButton>
qmake                   : QT += widgets
Inherits                : QAbstractButton -> QWidget -> QObject and QPaintDevice
Code                    : QPushButton* bn = new QPushButton("Close");


QLabel
--------------------
Qt5 QLabel class        : http://doc.qt.io/qt-5/qlabel.html
Header                  : #include <QLabel>
qmake                   : QT += widgets
Inherits                : QFrame -> QWidget -> QObject and QPaintDevice
Code                    : QLabel* label = new QLabel("Double:");


QLineEdit
--------------------
Qt5 QLineEdit class     : http://doc.qt.io/qt-5/qlineedit.html
Header                  : #include <QLineEdit>
qmake                   : QT += widgets
Inherits                : QWidget ->  QObject and QPaintDevice
Code                    : QLineEdit* edit = new QLineEdit();
               QObject::connect(edit,                                // sender
                                SIGNAL(textChanged(const QString&)), // signal
                                label,                               // receiver
                                SLOT(setText(const QString&)));      // slot


QCheckBox
--------------------
Qt5 QCheckBox class     : http://doc.qt.io/qt-5/qcheckbox.html
Header                  : #include <QCheckBox>
qmake                   : QT += widgets
Inherits                : QAbstractButton -> QWidget -> QObject and QPaintDevice
Code                    : QCheckBox* check = new QCheckBox("Enable");
                          check->setTristate(true);


QRadioButton
--------------------
Qt5 QRadioButton class  : http://doc.qt.io/qt-5/qradiobutton.html
Header                  : #include <QRadioButton>
qmake                   : QT += widgets
Inherits                : QAbstractButton -> QWidget -> QObject and QPaintDevice
Code                    : QGroupBox box("From around button group", &dlg);
                          QButtonGroup* group = new QButtonGroup(&box);
                          QRadioButton* radio1 = new QRadioButton("simple");
                          QRadioButton* radio2 = new QRadioButton("complex");
                          group->addButton(radio1);
                          group->addButton(radio2);

QGroupBox
--------------------
Qt5 QGroupBox class     : http://doc.qt.io/qt-5/qgroupbox.html
Header                  : #include <QGroupBox>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    : QGroupBox box("From around button group", &dlg);
                          QButtonGroup* group = new QButtonGroup(&box);
                          QRadioButton* radio1 = new QRadioButton("simple");
                          QRadioButton* radio2 = new QRadioButton("complex");
                          group->addButton(radio1);
                          group->addButton(radio2);


QListWidget
--------------------
Qt5 QListWidget class   : http://doc.qt.io/qt-5/qlistwidget.html
Header                  : #include <QListWidget>
qmake                   : QT += widgets
Inherits                : QListView -> QAbstractItemView -> QAbstractScrollArea
                          -> QFrame -> QWidget -> QObject and QPaintDevice
Code                    : QListWidget* list = new QListWidget();
                          QStringList items;
                          items << "Europe" << "North America" << "Australia";
                          list->addItems(items);

QComboBox
--------------------
Qt5 QComboBox class     : http://doc.qt.io/qt-5/qcombobox.html
Header                  : #include <QComboBox>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    : QComboBox* combo = new QComboBox();
                          QStringList items;
                          items << "foo" << "bar" << "baz";
                          combo->addItems(items);


QSpinBox
--------------------
Qt5 QSpinBox class      : http://doc.qt.io/qt-5/qspinbox.html
Header                  : #include <QSpinBox>
qmake                   : QT += widgets
Inherits                : QAbstractSpinBox -> QWidget-> QObject and QPaintDevice
Code                    : QSpinBox* spin = new QSpinBox();
                          spin->setRange(0, 100);


QTimeEdit
--------------------
Qt5 QTimeEdit class     : http://doc.qt.io/qt-5/qtimeedit.html
Header                  : #include <QTimeEdit>
qmake                   : QT += widgets
Inherits                : QDateTimeEdit -> QAbstractSpinBox ->  QWidget
                          -> QObject and QPaintDevice
Code                    : QTimeEdit* time = new QTimeEdit();


QDateEdit
--------------------
Qt5 QDateEdit class     : http://doc.qt.io/qt-5/qdateedit.html
Header                  : #include <QDateEdit>
qmake                   : QT += widgets
Inherits                : QDateTimeEdit -> QAbstractSpinBox ->  QWidget
                          -> QObject and QPaintDevice
Code                    : QDateEdit* date = new QDateEdit();


QDateTimeEdit
--------------------
Qt5 QDateTimeEdit class : http://doc.qt.io/qt-5/qdatetimeedit.html
Header                  : #include <QDateTimeEdit>
qmake                   : QT += widgets
Inherits                : QAbstractSpinBox -> QWidget-> QObject and QPaintDevice
Code                    : QDateTimeEdit* time = new QDateTimeEdit();


QCalendarWidget
--------------------
Qt5 QCalendarWidget     : http://doc.qt.io/qt-5/qcalendarwidget.html
Header                  : #include <QCalendarWidget>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    : QCalendarWidget* cal = new QCalendarWidget();


QSlider
--------------------
Qt5 QSlider class       : http://doc.qt.io/qt-5/qslider.html
Header                  : #include <QSlider>
qmake                   : QT += widgets
Inherits                : QAbstractSlider -> QWidget -> QObject and QPaintDevice
Code                    : QSlider* slider = new QSlider(Qt::Horizontal);
                          slider->setRange(0, 100);


QProgressBar
--------------------
Qt5 QProgressBar class  : http://doc.qt.io/qt-5/qprogressbar.html
Header                  : #include <QProgressBar>
qmake                   : QT += widgets
Inherits                : QWidget -> QObject and QPaintDevice
Code                    : use qtcreator


QFileDialog
--------------------
Qt5 QFileDialog class   : http://doc.qt.io/qt-5/qfiledialog.html
Header                  : #include <QFileDialog>
qmake                   : QT += widgets
Inherits                : QDialog -> QWidget -> QObject and QPaintDevice
Code                    : QFileDialog::getOpenFileName(0, caption, path, filter)
                          QFileDialog::getSaveFileName(0, caption, path, filter)
                          QFileDialog::getExistingDirectory(0, caption, path)


QMessageBox
--------------------
Qt5 QMessageBox class   : http://doc.qt.io/qt-5/qmessagebox.html
Header                  : #include <QMessageBox>
qmake                   : QT += widgets
Inherits                : QDialog -> QWidget -> QObject and QPaintDevice
Code                    : QMessageBox::information(0, title, message);
                          QMessageBox::warning(0, title, message);
                          QMessageBox::critical(0, title, message);
                          QMessageBox::question(0, title, question, Yes|No..);


QInputDialog
--------------------
Qt5 QInputDialog class  : http://doc.qt.io/qt-5/qinputdialog.html
Header                  : #include <QInputDialog>
qmake                   : QT += widgets
Inherits                : QDialog -> QWidget -> QObject and QPaintDevice
Code                    : double val = QInputDialog::getDouble(...);
                          int val    = QInputDialog::getInt(...);
                          QString s  = QInputDialog::getItem(...)
                          QString s  = QInputDialog::getMultiLineText(...);
                          QString s  = QInputDialog::getText(...);

QColorDialog
--------------------
Qt5 QColorDialog class  : http://doc.qt.io/qt-5/qcolordialog.html
Header                  : #include <QColorDialog>
qmake                   : QT += widgets
Inherits                : QDialog -> QWidget -> QObject and QPaintDevice
Code                    : QColor color = QColorDialog::getColor(
                                                Qt::yellow, NULL, title);


QFontDialog
--------------------
Qt5 QFontDialog class   : http://doc.qt.io/qt-5/qfontdialog.html
Header                  : #include <QFontDialog>
qmake                   : QT += widgets
Inherits                : QDialog -> QWidget -> QObject and QPaintDevice
Code                    : QFont font = QFontDialog::getFont(
                                             &ok, QFont("Arial", 18),0, title);


QValidator
--------------------
Qt5 QValidator class    : http://doc.qt.io/qt-5/qvalidator.html
Header                  : #include <QValidator>
qmake                   : QT += gui
Inherits                : QObject
Code                    : QLineEdit* intEdit = new QLineEdit("42");
                          QIntValidator intValidator(0, 100); //bottom, top
                          intEdit->setValidator(&intValidator);


QRegExp
--------------------
Qt5 QRegExp class       : http://doc.qt.io/qt-5/qregexp.html
Header                  : #include <QRegExp>
qmake                   : QT += core
Inherits                :
Code                    : QRegExp re("^\\+\\d{1,2}\\([089]\\)\\d{2,5}\\-\\d+$");

QRegExpValidator
--------------------
Qt5 QRegExpValidator    : http://doc.qt.io/qt-5/qregexpvalidator.html
Header                  : #include <QRegExpValidator>
qmake                   : QT += gui
Inherits                : QValidator
Code                    : QLineEdit* reEdit = new QLineEdit("+46(0)31-445566");
                          QRegExp re("^\\+\\d{1,2}\\([089]\\)\\d{2,5}\\-\\d+$");
                          QRegExpValidator reValidator(re);
                          reEdit->setValidator(&reValidator);
