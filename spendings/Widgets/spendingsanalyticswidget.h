#ifndef SPENDINGSANALYTICSWIDGET_H
#define SPENDINGSANALYTICSWIDGET_H

#include <QWidget>

#include "charts/linechart.h"
#include "analyticswidget.h"

class SpendingsAnalyticsWidget : public AnalyticsWidget
{
    Q_OBJECT
public:
    SpendingsAnalyticsWidget(QWidget* parent = nullptr);

    void setData(const QMap<int, double>& data);

private:
    LineChart* m_monthChart {nullptr};
    LineChart* m_yearChart {nullptr};

    QStringList m_months;
    QList<int> m_monthBorders;
};

#endif // SPENDINGSANALYTICSWIDGET_H
