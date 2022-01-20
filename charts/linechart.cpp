#include "linechart.h"

LineChart::LineChart(const QString &title, const QStringList& labels, const QList<int>& borders) : CustomChart(title)
{
    m_lineSeries = new QLineSeries(this);
    addSeries(m_lineSeries);

    if (labels.isEmpty())
    {
        m_xAxis = new QValueAxis(this);
    }
    else
    {
        auto categoryAxis = new QCategoryAxis(this);

        for (int i = 0; i < labels.size(); i++)
        {
            categoryAxis->append(labels[i], borders[i]);
        }

        m_xAxis = categoryAxis;
    }

    addAxis(m_xAxis, Qt::AlignBottom);

    m_yAxis = new QValueAxis(this);
    m_yAxis->setMax(100);
    addAxis(m_yAxis, Qt::AlignLeft);

    m_lineSeries->attachAxis(m_xAxis);
    m_lineSeries->attachAxis(m_yAxis);
}

void LineChart::setData(const QMap<int, double>& data)
{
    m_lineSeries->clear();

    QList<int> labels = data.keys();

    m_xAxis->setMin(labels.first());
    m_xAxis->setMax(labels.last());

    int lastPoint = 0;
    for (int label : labels)
    {
        double value = data[label];
        m_lineSeries->append(label, value + lastPoint);
        lastPoint += value;
    }

    m_yAxis->setMin(0);
    m_yAxis->setMax(lastPoint);
}
