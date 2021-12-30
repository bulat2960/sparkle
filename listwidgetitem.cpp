#include "listwidgetitem.h"

ListWidgetItem::ListWidgetItem(QWidget* widget, QListWidget* parent)
    : QListWidgetItem(parent),
      m_widget(widget)
{
    setSizeHint(widget->minimumSizeHint());
    setBackground(QBrush(QColor(180, 180, 180, 255)));
}

void ListWidgetItem::changeSortingOrder(const QString& sortingOrderString)
{
    m_sortingOrderString = sortingOrderString;
}
