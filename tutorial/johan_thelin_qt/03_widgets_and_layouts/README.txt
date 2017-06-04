********************************************************************************
                        Chapter 3. Widgets and Layouts
********************************************************************************
1. Qt5 classes hierarchy
------------------------

   http://doc.qt.io/qt-5/hierarchy.html


2. Setup the environment (already explained in cap.2)
-----------------------------------------------------
    export PATH=/usr/lib64/qt5/bin:$PATH
    which qmake; which moc; which uic;
/usr/lib64/qt5/bin/qmake
/usr/lib64/qt5/bin/moc
/usr/lib64/qt5/bin/uic


3. Create a project
-------------------
    touch main.cpp
    qmake -project $PWD/main.cpp -o project.pro
    qtcreator project.pro
    add new-> Qt Designer Form Class -> Dialog with Buttons Bottom,
           -> Choose a Class Name | DesignerDlg, File Name: designerdlg.cpp,h,ui
           -> Add to project and source control.
    qmake -makefile -o Makefile "QT+=widgets" project.pro
    make
    ./project
    git clean -f .


4. Layouts
----------
    Vertical layout, where all widgets are stacked vertically.
    Horizontal layout, where all widges are stacked horizontally.
    Grid layout, where one widget can span one or more cells in table-like grid.
