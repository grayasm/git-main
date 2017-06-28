#include "InfoWidget.h"


InfoWidget::InfoWidget(QWidget *parent) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setWordWrap(true);

    setText(tr("Ready"));
}


void InfoWidget::documentChanged(int position, int charsRemoved, int charsAdded)
{
    QString text;

    if(charsRemoved)
        text = tr("%1 removed").arg(charsRemoved);

    if(charsRemoved && charsAdded)
        text += tr(", ");

    if(charsAdded)
        text += tr("%1 added").arg(charsAdded);

    setText(text);
}
