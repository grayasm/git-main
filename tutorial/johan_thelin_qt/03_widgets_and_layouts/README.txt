********************************************************************************
                        Chapter 3. Widgets and Layouts
********************************************************************************

1. Setup the environment (already explained in cap.2)
-----------------------------------------------------
    export PATH=/usr/lib64/qt5/bin:$PATH


2. Create a project
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


3. Size Policies set by Qt Designer
-----------------------------------
    qmake -project -nopwd $PWD/01_size_policies_designer.cpp \
                          $PWD/01_designerdlg.cpp \
                          $PWD/01_designerdlg.h \
                          $PWD/01_designerdlg.ui \
                          -o designer.pro
    qmake -makefile -o Makefile "QT+=widgets" designer.pro
    make

