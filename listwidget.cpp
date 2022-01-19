#include "listwidget.h"

#include <QScrollBar>

ListWidget::ListWidget(QWidget* parent) : QListWidget(parent)
{
    setSpacing(5);

    verticalScrollBar()->hide();
    verticalScrollBar()->setStyleSheet("QScrollBar { width: 0px; }");

    setSelectionMode(QListWidget::NoSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);

    setSortingEnabled(true);

    setStyleSheet("ListWidget { background: darkgreen; }"
                  "ListWidget::item { border-radius: 10px; background: rgb(180, 180, 180); }");

    connect(this, &ListWidget::customContextMenuRequested, this, &ListWidget::showContextMenu);
}

QAction* ListWidget::createSortingRequestAction(const QString& text, Qt::SortOrder order)
{
    auto action = new QAction(text, this);

    connect(action, &QAction::triggered, this, [this, text, order]
    {
        setSortingEnabled(true);
        emit sortingOrderChangeRequested(text);
        sortItems(order);
    });

    return action;
}

void ListWidget::sort()
{
    sortItems();
}

void ListWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        m_lastClickedItem = dynamic_cast<ListWidgetItem*>(itemAt(event->pos()));
    }
}
