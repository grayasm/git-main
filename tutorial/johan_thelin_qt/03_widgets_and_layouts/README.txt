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


4. Size Policies set in the code directly
-----------------------------------------
    qmake -project -nopwd $PWD/02_size_policies_coding.cpp -o project.pro
    qmake -makefile -o Makefile "QT+=widgets" project.pro
    make


5. Layouts
----------
    Vertical layout, where all widgets are stacked vertically.
    Horizontal layout, where all widges are stacked horizontally.
    Grid layout, where one widget can span one or more cells in table-like grid.
