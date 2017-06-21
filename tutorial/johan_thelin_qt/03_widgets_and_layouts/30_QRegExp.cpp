/*
  Regular Expressions

  Imagine having to validate a phone number structured like +nn(p)aa...a-ll...l,
  where:
       n represents the nation number,
       p the local area code prefix,
       a an area code, and l the local number within that area.

  There can be one to two digits in the nation number. The local area prefix
  can be 0, 8, or 9 (let’s say two to five numbers in the area code and at
  least one digit in the local number).
  In this situation a regular expression can be your savior.

  Build:
  qmake -project -nopwd $PWD/30_QRegExp.cpp -o 30_project.pro
  qmake -makefile -o Makefile "QT+=widgets" 30_project.pro
  make
  ./30_project
  git clean -f .
 */


#include <QtWidgets/QtWidgets>
#include <QRegExp>
#include <iostream>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);


    // matching phone numbers with regular expressions

    QRegExp re("^\\+\\d{1,2}\\([089]\\)\\d{2,5}\\-\\d+$");

    std::cout << re.indexIn("+46(0)31-445566") << std::endl;
    std::cout << re.indexIn("Tel: +46(0)31-445566") << std::endl;
    std::cout << re.indexIn("(0)31-445566") << std::endl;


    // capturing the different parts of the phone number using a regular
    // expression with capturing parantheses

    QRegExp reCap("^\\+(\\d{1,2})\\(([089])\\)(\\d{2,5})\\-(\\d+)$");
    std::cout << reCap.indexIn("+46(0)31-445566") << std::endl;
    std::cout << reCap.cap(0).toStdString() << std::endl;
    std::cout << reCap.cap(1).toStdString() << std::endl;
    std::cout << reCap.cap(2).toStdString() << std::endl;
    std::cout << reCap.cap(3).toStdString() << std::endl;
    std::cout << reCap.cap(4).toStdString() << std::endl;



    // no need for the message loop, return to system
    return 0;
}
