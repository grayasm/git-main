/*
  Sample dialog with 2 QPushButton(s) connected to 2 slots.


  Build:
  qmake -project -nopwd $PWD/07_QPushButton.cpp   \
                        $PWD/07_QPushButton.h     \
                        -o 07_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 07_project.pro
  make
  ./07_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include <07_QPushButton.h>

QPushButton* gbn = NULL;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QDialog dlg;

    QPushButton* clickbn = new QPushButton("Click me!");
    QPushButton* togglebn = new QPushButton("Toggle me!");
    togglebn->setCheckable(true);
    gbn = togglebn;

    QHBoxLayout* layout = new QHBoxLayout(&dlg);
    layout->addWidget(clickbn);
    layout->addWidget(togglebn);

    Simple* simple = new Simple(&dlg);
    QObject::connect(clickbn,                   // sender
                     SIGNAL(clicked()),         // signal
                     simple,                    // receiver
                     SLOT(buttonClicked()));    // slot

    QObject::connect(togglebn,                  // sender
                     SIGNAL(clicked()),         // signal
                     simple,                    // receiver
                     SLOT(buttonToggled()));    // slot

    dlg.show();
    return app.exec();
}


void Simple::buttonClicked()
{
    QMessageBox::information(NULL, "Clicked!", "The button was clicked!");
}

void Simple::buttonToggled()
{
    QString state = gbn->isChecked() ? "pressed" : "released";
    QString text("The button is ");
    text += state;
    text += "!";
    QMessageBox::information(NULL, "Toggled!", text);
}
