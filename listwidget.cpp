#include "listwidget.h"

#include <QScrollBar>

ListWidget::ListWidget(QWidget* parent) : QListWidget(parent)
{
    setSpacing(5);

    verticalScrollBar()->hide();

    setSelectionMode(QListWidget::NoSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);

    setVerticalScrollMode(ListWidget::ScrollPerPixel);

    m_scrollAnimation = new QPropertyAnimation(verticalScrollBar(), "value", this);
    m_scrollAnimation->setDuration(50);

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

void ListWidget::updateGeometries()
{
    QListView::updateGeometries();
    verticalScrollBar()->setSingleStep(1);
}

void ListWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        m_lastClickedItem = dynamic_cast<ListWidgetItem*>(itemAt(event->pos()));
    }
}

void ListWidget::wheelEvent(QWheelEvent* event)
{
    int direction = event->angleDelta().y() < 0 ? 100 : -100;

    if (m_scrollAnimation->state() == QPropertyAnimation::Running)
    {
        m_scrollAnimation->stop();
    }
    m_scrollAnimation->setStartValue(verticalScrollBar()->value());
    m_scrollAnimation->setEndValue(verticalScrollBar()->value() + direction);
    m_scrollAnimation->start();
}
