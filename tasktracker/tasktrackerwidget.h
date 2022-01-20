#ifndef TASKTRACKERWIDGET_H
#define TASKTRACKERWIDGET_H

#include "Widgets/tasklistwidget.h"
#include "task.h"
#include "Utility/timercontroller.h"

#include <QTimer>
#include <QTabWidget>

class TaskTrackerWidget : public QTabWidget
{
    Q_OBJECT

public:
    TaskTrackerWidget(QWidget* parent = nullptr);
    ~TaskTrackerWidget();

    void loadData();
    void saveData();

signals:
    void popupCreateRequested(const QString& title, const QString& message);

private slots:
    void appendTask(Task* task);
    void removeTask(Task* task);

    void setupTaskListWidget(TaskListWidget* taskListWidget, const QString &tabName);

private:
    QList<Task*> m_tasks;

    TimerController* m_timerController {nullptr};

    TaskListWidget* m_repeatableTasksWidget {nullptr};
    TaskListWidget* m_oneTimeTasksWidget {nullptr};
};

#endif // TASKTRACKERWIDGET_H
