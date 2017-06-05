/*
  The radio button is a close relative of the checkbox. It works like
  a checkbox, except that only one in a group can be checked each time.
  After you have checked a box in a group, you cannot remove the check;
  you can move it only within the group. This means that if you check one
  box programmatically when you initialize your dialog, you are guaranteed
  that one of the boxes is checked at all times. To monitor the state of
  the buttons, use the toggled(bool) signal and the isChecked method.

  A group of radio buttons consists of all buttons with the same parent widget.
  If you do not want to split them visually, you can use a QButtonGroup.

  This sample creates confusion because radio buttons are not separated visually
  into QGroupBox(es), but using a minimal approach with QButtonGroup.



  Build with:
  qmake -project -nopwd $PWD/11_QRadioButton.cpp -o project.pro
  qmake -makefile -o Makefile "QT+=widgets" project.pro
  make
  ./project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QGroupBox box("Printing Options", &dlg);

    QRadioButton* portrait = new QRadioButton("Portrait");
    QRadioButton* landscape = new QRadioButton("Landscape");
    QRadioButton* color = new QRadioButton("Color");
    QRadioButton* bw = new QRadioButton("B&W");

    QButtonGroup* orientation = new QButtonGroup(&box);
    QButtonGroup* colorBw = new QButtonGroup(&box);

    orientation->addButton(portrait);
    orientation->addButton(landscape);
    colorBw->addButton(color);
    colorBw->addButton(bw);

    QGridLayout* grid = new QGridLayout(&box);
    grid->addWidget(portrait, 0, 0);
    grid->addWidget(landscape, 0, 1);
    grid->addWidget(color, 1, 0);
    grid->addWidget(bw, 1, 1);

    dlg.show();
    return app.exec();
}
