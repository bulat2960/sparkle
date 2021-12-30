#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QChartView>

class CustomChartView : public QChartView
{
    Q_OBJECT

public:
    CustomChartView(QChart* m_chart, QWidget* parent = nullptr);
};

#endif // CUSTOMCHARTVIEW_H
