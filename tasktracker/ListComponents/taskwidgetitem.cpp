#include "taskwidgetitem.h"

TaskWidgetItem::TaskWidgetItem(TaskWidget* taskWidget, QListWidget* parent)
    : ListWidgetItem(taskWidget, parent)
{
    m_taskWidget = taskWidget;
}

bool TaskWidgetItem::operator<(const QListWidgetItem& other) const
{
    const TaskWidgetItem* otherTaskWidgetItem = dynamic_cast<const TaskWidgetItem*>(&other);

    if (otherTaskWidgetItem == nullptr)
    {
        return QListWidgetItem::operator<(other);
    }

    if (m_sortingOrderString.contains("Periodicity"))
    {
        return m_taskWidget->task()->periodicity() < otherTaskWidgetItem->m_taskWidget->task()->periodicity();
    }
    else if (m_sortingOrderString.contains("Deadline"))
    {
        return m_taskWidget->task()->deadline() < otherTaskWidgetItem->m_taskWidget->task()->deadline();
    }
    else if (m_sortingOrderString.contains("Completion time"))
    {
        return m_taskWidget->task()->completionTime() < otherTaskWidgetItem->m_taskWidget->task()->completionTime();
    }
    else if (m_sortingOrderString.contains("Status"))
    {
        Task::Status currentTaskStatus = m_taskWidget->task()->status();
        Task::Status otherTaskStatus = otherTaskWidgetItem->m_taskWidget->task()->status();

        if (currentTaskStatus == otherTaskStatus)
        {
            return m_taskWidget->task()->name() < otherTaskWidgetItem->m_taskWidget->task()->name();
        }

        return currentTaskStatus < otherTaskStatus;
    }

    return QListWidgetItem::operator<(other);
}

TaskWidget* TaskWidgetItem::taskWidget() const
{
    return m_taskWidget;
}
