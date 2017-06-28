#ifndef __InfoWidget_h__
#define __InfoWidget_h__


#include <QtWidgets/QtWidgets>

class InfoWidget : public QLabel
{
    Q_OBJECT

public:
    InfoWidget(QWidget* parent = 0);

public slots:
    void documentChanged(int position, int charsRemoved, int charsAdded);
};

#endif // __InfoWidget_h__
