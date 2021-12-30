#include "englishanalyticswidget.h"

#include <QChartView>
#include <QGridLayout>

EnglishAnalyticsWidget::EnglishAnalyticsWidget(QWidget *parent) : AnalyticsWidget(parent)
{
    m_categoriesChart = new PieChart("Categories");
    m_categoriesChart->setDisplayedLabelFormat(QStringLiteral("%1 (%2)"));

    m_learningQualityChart = new PieChart("Learning quality");
    m_learningQualityChart->setDisplayedLabelFormat(QStringLiteral("%1 (%2)"));

    auto gridLayout = new QGridLayout(this);
    gridLayout->addWidget(createCustomChartView(m_categoriesChart), 0, 0);
    gridLayout->addWidget(createCustomChartView(m_learningQualityChart), 0, 1);
    gridLayout->addWidget(createCustomChartView(new PieChart("Empty chart")), 1, 0);
    gridLayout->addWidget(createCustomChartView(new PieChart("Empty chart")), 1, 1);
}

void EnglishAnalyticsWidget::setCategoriesData(const QMap<QString, double>& data)
{
    m_categoriesChart->setData(data.keys(), data.values());
}

void EnglishAnalyticsWidget::setLearningQualityData(const QMap<double, double>& data)
{
    QMap<QString, double> modifiedData;

    for (const auto& percentage : data.keys())
    {
        if (percentage < 25)
        {
            modifiedData["0-25%"] += data[percentage];
        }
        else if (percentage < 50)
        {
            modifiedData["25-50%"] += data[percentage];
        }
        else if (percentage < 75)
        {
            modifiedData["50-75%"] += data[percentage];
        }
        else
        {
            modifiedData["75-100%"] += data[percentage];
        }
    }

    m_learningQualityChart->setData(modifiedData.keys(), modifiedData.values());
}
