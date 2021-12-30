#include "spendingsanalyticswidget.h"

#include <QVBoxLayout>
#include <QDate>

SpendingsAnalyticsWidget::SpendingsAnalyticsWidget(QWidget* parent) : AnalyticsWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    m_months = {"January", "February", "March", "April",
                "May", "June", "July", "August", "September",
                "October", "November", "December"};

    m_monthBorders = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

    m_yearChart = new LineChart("Year spendings", m_months, m_monthBorders);


    QList<int> monthDays;
    QStringList monthDaysLabels;

    int currentMonthDays = QDate::currentDate().daysInMonth();

    for (int i = 0; i <= currentMonthDays; i++)
    {
        monthDays.append(i);
        monthDaysLabels.append(QString::number(i));
    }

    m_monthChart = new LineChart("Month spendings", monthDaysLabels, monthDays);

    layout->addWidget(createCustomChartView(m_yearChart));
    layout->addWidget(createCustomChartView(m_monthChart));
}

void SpendingsAnalyticsWidget::setData(const QMap<int, double>& data)
{
    int currentMonth = QDate::currentDate().month();

    int currentMonthBorder = m_monthBorders[currentMonth - 1];
    int prevMonthBorder = (currentMonth == 1) ? 0 : m_monthBorders[currentMonth - 2];


    m_yearChart->setData(data);

    QMap<int, double> monthData;
    monthData[0] = 0;

    for (int label : data.keys())
    {
        double value = data[label];


        if (label > prevMonthBorder and label <= currentMonthBorder)
        {
            monthData[label - prevMonthBorder] = value;
        }
    }

    m_monthChart->setData(monthData);
}
