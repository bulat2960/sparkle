#ifndef ENGLISHANALYTICSWIDGET_H
#define ENGLISHANALYTICSWIDGET_H

#include <QWidget>

#include "charts/piechart.h"
#include "analyticswidget.h"

class EnglishAnalyticsWidget : public AnalyticsWidget
{
    Q_OBJECT
public:
    explicit EnglishAnalyticsWidget(QWidget *parent = nullptr);

    void setCategoriesData(const QMap<QString, double>& data);
    void setLearningQualityData(const QMap<double, double>& data);

signals:

private:
    PieChart* m_categoriesChart {nullptr};
    PieChart* m_learningQualityChart {nullptr};
};

#endif // ENGLISHANALYTICSWIDGET_H
