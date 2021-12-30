#ifndef LINECHART_H
#define LINECHART_H

#include "customchart.h"

#include <QLineSeries>
#include <QCategoryAxis>

class LineChart : public CustomChart
{
    Q_OBJECT

public:
    LineChart(const QString& title, const QStringList& labels = QStringList(), const QList<int>& borders = QList<int>());

    void setData(const QMap<int, double>& data);

private:
    QLineSeries* m_lineSeries {nullptr};

    QAbstractAxis* m_xAxis {nullptr};
    QValueAxis* m_yAxis {nullptr};
};

#endif // LINECHART_H
