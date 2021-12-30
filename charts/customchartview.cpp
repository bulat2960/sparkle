#include "customchartview.h"

CustomChartView::CustomChartView(QChart* chart, QWidget* parent) : QChartView(chart, parent)
{
    setBackgroundBrush(QBrush(Qt::lightGray));
}
