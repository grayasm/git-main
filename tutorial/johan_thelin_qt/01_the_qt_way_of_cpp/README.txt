********************************************************************************
        Chapter 1  The Qt Way of C++
********************************************************************************
INSTALL:
--------------------------------------------------------------------------------
    yum install yum-utils
    repoquery -l qt5-qtbase-devel
    yum install qt5-qtbase-devel

    # /usr/include/qt5/QtConcurrent/<headers>
    # /usr/include/qt5/QtCore/<headers, QList,QVector,QMap,etc>
    # /usr/include/qt5/QtDBus/<headers>
    # /usr/include/qt5/QtGui/<headers, QBrush,QColor,QFont,etc>
    # /usr/include/qt5/QtNetwork/<headers>
    # /usr/include/qt5/QtOpenGL/<headers, QGLBuffer,QGLWidget,etc>
    # /usr/include/qt5/QtPlatformHeaders/<headers>
    # /usr/include/qt5/QtPrintSupport/<headers, QPrintDialog,etc>
    # /usr/include/qt5/QtSql/<headers, QSqlDatabase,QSqlQuery,etc>
    # /usr/include/qt5/QtTest/<headers, QTest,QtTestGui,QtTestWidgets,etc>
    # /usr/include/qt5/QtWidgets/<headers, QApplication,QLabel,QLineEdit,etc>
    # /usr/include/qt5/QtXml/<headers, QXmlReader,etc>

    yum provides "*/bin/qmake"
    yum provides "*/bin/moc"
    yum provides "*/bin/uic"

qt5-qtbase-devel-5.6.1-10.el7.x86_64 : Development files for qt5-qtbase
Repo        : base
Matched from:
Filename    : /usr/lib64/qt5/bin/uic

     export PATH=/usr/lib64/qt5/bin:$PATH

PROJECT:
--------------------------------------------------------------------------------
    # http://doc.qt.io/qt-5/qmake-manual.html

    which qmake
/usr/lib64/qt5/bin/qmake

    qmake -project -nopwd $PWD/file1 $PWD/file2 ... $PWD/filen \
          -o project.pro
    qmake
    make
    ./project
    git clean -f .

MOC:
--------------------------------------------------------------------------------
    # http://doc.qt.io/qt-5/moc.html
    The meta object compiler handles Qt C++ extensions and parses only C++
    header files! (important, don't write moc items in .cpp,.cxx,.cc,etc)

class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass(QObject *parent = 0);
    ~MyClass();

signals:
    void mySignal();

public slots:
    void mySlot();
};


    # connect a signal to a slot
    QObject::connect(
        objA, SIGNAL(mySignal()),
        objB, SLOT(mySlot()));

    # emit a signal from a slot method
    emit mySignal();

    # always avoid an inifinite loop
    void mySlot(int val)
    {
        if (val == m_val) return;
        m_val = val;
        emit mySignal(m_val);
    }

    # a parent deletes its children automatically
    MyClass(QObject* parent) : QObject(parent) {}


QTCREATOR:
--------------------------------------------------------------------------------
    yum install qt-creator
    qtcreator project.pro &


CODING:
--------------------------------------------------------------------------------
    Qt uses CamelCasing convention, like this: ThisIsAnExample.
    Qt classes are prefixed with a Q, like this: QMessageBox.
    Qt 3rd party classes are prefixed by a Q and a set of lowercase letters: QjColorPicker.
    Include class QMessageBox header like this: #include <QMessageBox>
    Method names start with lowercase letters, ex: void thisIsAMethod();
    foo getter is:          int  foo() const;
    foo setter is:          void setFoo(int);
    foo changed signal  is: void fooChanged(int);
    A slot method is like a setter: void setColor(int r, int g, int b);
    A signal is a prototype only:   void colorChanged(int, r, int g, int b);
    A slot method emits a signal like:  emit ColorChanged(r,g,b);
    A slot method must test if the value changed before emitting the signal.
    (to avoid an infinite loop)
    QObject::connect method handles only argument types , not values.
    Class must inherit QObject and start declaration with Q_OBJECT to use
    slots and signals.
    Set the QObject parent to delete class instance automatically.
    Qt implements similar STL containers even on platform without stl support.
