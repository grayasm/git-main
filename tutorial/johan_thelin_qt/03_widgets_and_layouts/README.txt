********************************************************************************
                        Chapter 3. Widgets and Layouts
********************************************************************************

1. Setup the environment (already explained in cap.2)
-----------------------------------------------------
    export PATH=/usr/lib64/qt5/bin:$PATH

2. How to build again this project from scratch
-----------------------------------------------
    The first example 01_size_policies_designer.cpp has these steps:

    a) create empty file  01_size_policies_designer.cpp
    b) create project(pro) file with qmake -project designer.pro
    c) start qtcreator with qtcreator designer.pro
    d) add new-> Qt Designer Form Class -> Dialog with Buttons Bottom,
       -> Choose a Class Name | DesignerDlg, File Name: 01_designerdlg.cpp,h,ui
       -> Add to project and source control.
    e) add content for int main(int, char**)
    f) create makefile with qmake -makefile -o Makefile "QT+=widgets" designer.pro
    g) make and run


3. How to compile the samples
-----------------------------
    qmake -project -nopwd $PWD/01_size_policies_designer.cpp \
                          $PWD/01_designerdlg.cpp \
                          $PWD/01_designerdlg.h \
                          $PWD/01_designerdlg.ui \
                          -o designer.pro
    qmake -makefile -o Makefile "QT+=widgets" designer.pro
    make
