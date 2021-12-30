#ifndef ANALYTICSWIDGET_H
#define ANALYTICSWIDGET_H

#include <QWidget>

#include "charts/customchartview.h"
#include "charts/customchart.h"

class AnalyticsWidget : public QWidget
{
    Q_OBJECT

public:
    AnalyticsWidget(QWidget* parent = nullptr);

    CustomChartView* createCustomChartView(CustomChart* chart);
};

#endif // ANALYTICSWIDGET_H
