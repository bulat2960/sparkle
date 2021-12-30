#ifndef PIECHART_H
#define PIECHART_H

#include "customchart.h"

#include <QPieSeries>

class PieChart : public CustomChart
{
public:
    PieChart(const QString& title);

    void setData(const QStringList& labels, const QList<double>& values);

private:
    QPieSeries* m_pieSeries {nullptr};

    void updatePieSlice(const QString& label, qreal value);

    QMap<QString, QPieSlice*> m_pieSliceMap;
};

#endif // PIECHART_H
