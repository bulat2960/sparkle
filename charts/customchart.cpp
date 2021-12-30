#include "customchart.h"

CustomChart::CustomChart(const QString& title)
{
    setTitle(title);

    QFont font;
    font.setPixelSize(20);
    setTitleFont(font);

    legend()->hide();

    setBackgroundBrush(QBrush(Qt::lightGray));
}

void CustomChart::setDisplayedLabelFormat(const QString& displayedLabelFormat)
{
    m_displayedLabelFormat = displayedLabelFormat;
}
