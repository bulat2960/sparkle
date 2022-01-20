#include "tasklistwidget.h"

#include <QPushButton>
#include <QScrollBar>
#include <QMessageBox>

#include "../Dialogs/createtaskdialog.h"

TaskListWidget::TaskListWidget(TaskListWidget::Type type, QWidget* parent) : ListWidget(parent), m_type(type)
{
    setSpacing(5);

    setContextMenuPolicy(Qt::CustomContextMenu);
}

void TaskListWidget::createDisplayedWidget(Task* task)
{
    setSortingEnabled(false);

    auto taskWidget = new TaskWidget(task, this);
    auto item = new TaskWidgetItem(taskWidget, this);
    setItemWidget(item, taskWidget);

    scrollToItem(item);

    // Add and remove subtasks
    connect(task, &Task::subtaskAdded, taskWidget, &TaskWidget::addSubtaskWidget);
    connect(task, &Task::subtaskRemoved, taskWidget, &TaskWidget::removeSubtaskWidget);

    // Change height to ensure subtasks visible
    connect(taskWidget, &TaskWidget::heightChanged, this, [item](int height)
    {
        item->setSizeHint(QSize(item->sizeHint().width(), height));
    });

    if (m_type == Type::OneTime)
    {
        connect(task, &Task::deadlineChanged, this, &TaskListWidget::sort);
        connect(task, &Task::completionTimeChanged, this, &TaskListWidget::sort);
    }
    else
    {
        connect(task, &Task::periodicityChanged, this, &TaskListWidget::sort);
        connect(task, &Task::statusChanged, this, &TaskListWidget::sort);
    }

    connect(this, &TaskListWidget::sortingOrderChangeRequested, item, &TaskWidgetItem::changeSortingOrder);

    connect(taskWidget, &TaskWidget::destroyed, this, [this, task]
    {
        emit taskRemoved(task);
    });
}

void TaskListWidget::showContextMenu(const QPoint& point)
{
    QPoint globalPos = mapToGlobal(point);

    QMenu menu;

    menu.addAction("Create new task", this, &TaskListWidget::createObject);

    QAction* removeAction = menu.addAction("Remove task", this, &TaskListWidget::removeObject);
    removeAction->setEnabled(m_lastClickedItem != nullptr);

    QMenu sortingMenu("Sort by...");
    menu.addMenu(&sortingMenu);

    if (m_type == Type::OneTime)
    {
        sortingMenu.addAction(createSortingRequestAction("Completion time (ascending)"));
        sortingMenu.addAction(createSortingRequestAction("Completion time (descending)", Qt::DescendingOrder));

        sortingMenu.addAction(createSortingRequestAction("Deadline (ascending)"));
        sortingMenu.addAction(createSortingRequestAction("Deadline (descending)", Qt::DescendingOrder));
    }
    else
    {
        sortingMenu.addAction(createSortingRequestAction("Periodicity (ascending)"));
        sortingMenu.addAction(createSortingRequestAction("Periodicity (descenging)", Qt::DescendingOrder));
    }

    sortingMenu.addAction(createSortingRequestAction("Status (ascending)"));
    sortingMenu.addAction(createSortingRequestAction("Status (descending)", Qt::DescendingOrder));

    menu.exec(globalPos);
}

void TaskListWidget::createObject()
{
    CreateTaskDialog dialog(m_type, this);
    int code = dialog.exec();

    if (code == QDialog::Accepted)
    {
        auto task = dialog.createTask();
        createDisplayedWidget(task);
        emit taskCreated(task);
    }
}

void TaskListWidget::removeObject()
{
    auto taskWidgetItem = dynamic_cast<TaskWidgetItem*>(m_lastClickedItem);
    auto taskWidget = taskWidgetItem->taskWidget();
    auto task = taskWidget->task();

    if (task->status() == Task::Status::Pending and task->subtasks().size() > 0)
    {
        int result = QMessageBox::question(this, "Delete task",
                                           "This task has unfinished subtasks. Do you really want to delete it?");

        if (result == QMessageBox::No)
        {
            return;
        }
    }

    m_lastClickedItem->deleteLater();
}
