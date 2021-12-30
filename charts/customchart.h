#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QChart>

class CustomChart : public QChart
{
public:
    CustomChart(const QString& title);

public:
    void setDisplayedLabelFormat(const QString& displayedLabelFormat);

protected:
    QString m_displayedLabelFormat;
};

#endif // CUSTOMCHART_H
