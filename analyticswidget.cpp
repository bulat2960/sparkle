#include "analyticswidget.h"

AnalyticsWidget::AnalyticsWidget(QWidget* parent) : QWidget(parent)
{

}

CustomChartView* AnalyticsWidget::createCustomChartView(CustomChart* chart)
{
    auto customChartView = new CustomChartView(chart, this);
    return customChartView;
}
