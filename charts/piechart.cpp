#include "piechart.h"

PieChart::PieChart(const QString& title) : CustomChart(title)
{
    m_pieSeries = new QPieSeries(this);
    addSeries(m_pieSeries);
}

void PieChart::setData(const QStringList& labels, const QList<double>& values)
{
    for (int i = 0; i < labels.size(); i++)
    {
        updatePieSlice(labels[i], values[i]);
    }
}

void PieChart::updatePieSlice(const QString& label, double value)
{
    QString displayedLabel = m_displayedLabelFormat.arg(label).arg(value);

    if (m_pieSliceMap.contains(label))
    {
        m_pieSliceMap[label]->setValue(value);
        m_pieSliceMap[label]->setLabel(displayedLabel);
    }
    else
    {
        auto pieSlice = new QPieSlice(displayedLabel, value);

        QFont font;
        font.setPixelSize(15);
        pieSlice->setLabelFont(font);

        pieSlice->setLabelVisible(true);

        m_pieSeries->append(pieSlice);
        m_pieSliceMap.insert(label, pieSlice);

    }
}
