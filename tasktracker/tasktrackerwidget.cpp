#include "tasktrackerwidget.h"

#include <QFile>
#include <QTextStream>
#include <QApplication>

TaskTrackerWidget::TaskTrackerWidget(QWidget* parent) : QTabWidget(parent)
{
    m_timerController = new TimerController(this);
    connect(m_timerController, &TimerController::deadlineNotified, this, &TaskTrackerWidget::popupCreateRequested);

    loadData();

    m_repeatableTasksWidget = new TaskListWidget(TaskListWidget::Type::Repeatable, this);
    setupTaskListWidget(m_repeatableTasksWidget, QStringLiteral("Repeatable"));

    m_oneTimeTasksWidget = new TaskListWidget(TaskListWidget::Type::OneTime, this);
    setupTaskListWidget(m_oneTimeTasksWidget, QStringLiteral("One-time"));

    tabBar()->setDocumentMode(true);

    for (Task* task : m_tasks)
    {
        if (task->periodicity().isValid())
        {
            m_repeatableTasksWidget->createDisplayedWidget(task);
        }
        else
        {
            m_oneTimeTasksWidget->createDisplayedWidget(task);
        }
    }

    m_repeatableTasksWidget->sort();
    m_oneTimeTasksWidget->sort();

    qRegisterMetaType<Task::Status>("Task::Status");
}

void TaskTrackerWidget::setupTaskListWidget(TaskListWidget* taskListWidget, const QString& tabName)
{
    addTab(taskListWidget, tabName);

    connect(taskListWidget, &TaskListWidget::taskCreated, this, &TaskTrackerWidget::appendTask);
    connect(taskListWidget, &TaskListWidget::taskRemoved, this, &TaskTrackerWidget::removeTask);
}

void TaskTrackerWidget::appendTask(Task* task)
{
    if (task->periodicity().isValid())
    {
        connect(task, &Task::periodicityChanged, m_timerController, [this, task]
        {
            m_timerController->registerPeriodicalTask(task);
        });

        m_timerController->registerPeriodicalTask(task);
    }

    if (not task->periodicity().isValid())
    {
        connect(task, &Task::deadlineChanged, m_timerController, [this, task]
        {
            m_timerController->registerOneTimeTask(task);
        });

        connect(task, &Task::statusChanged, m_timerController, [this, task]
        {
            if (task->status() != Task::Status::Pending)
            {
                m_timerController->unregisterTask(task);
            }
            else
            {
                task->setDeadline(QDateTime());
                m_timerController->registerOneTimeTask(task);
            }
        });

        if (task->deadline().isValid())
        {
            m_timerController->registerOneTimeTask(task);
        }
    }

    m_tasks.append(task);
}

void TaskTrackerWidget::removeTask(Task* task)
{
    m_tasks.removeOne(task);
    m_timerController->unregisterTask(task);
    task->deleteLater();
}

void TaskTrackerWidget::loadData()
{
    QFile file(QApplication::applicationDirPath() + "/data/todolist.txt");

    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to load todolist";
        return;
    }

    QTextStream fileStream(&file);

    while (not fileStream.atEnd())
    {
        QString line = fileStream.readLine();

        if (line.isEmpty())
        {
            continue;
        }

        QStringList data = line.split(" : ");

        if (not (line.first(3) == " - "))
        {
            QString name = data[0];
            int status = data[1].toInt();
            TimeSpan periodicity = TimeSpan().addSeconds(data[2].toInt());
            QDateTime deadline = QDateTime::fromString(data[3], QStringLiteral("dd-MM-yyyy hh:mm"));
            QDateTime completionTime = QDateTime::fromString(data[4], QStringLiteral("dd-MM-yyyy hh:mm"));

            auto task = new Task(name, status, periodicity, deadline, completionTime);

            bool taskCompleted = completionTime.isValid();
            bool hasDeadline = deadline.isValid();
            bool deadlineExpired = deadline < QDateTime::currentDateTime();
            bool isPeriodical = periodicity.isValid();

            if (not taskCompleted and hasDeadline and deadlineExpired and not isPeriodical)
            {
                task->setStatus(Task::Status::Failed);
            }

            appendTask(task);
        }
        else
        {
            QString name = data[0].remove(0, 3);
            int status = data[1].toInt();

            auto lastAddedTask = m_tasks.last();
            lastAddedTask->addSubtask(new Task(name, status));
        }
    }

    file.close();
}

void TaskTrackerWidget::saveData()
{
    QFile file(QApplication::applicationDirPath() + "/data/todolist.txt");

    if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to save todolist";
        return;
    }

    QTextStream fileStream(&file);

    for (Task* task : m_tasks)
    {
        fileStream << task->name() << " : " << task->status() << " : " << task->periodicity().seconds() << " : " <<
                      task->deadline().toString("dd-MM-yyyy hh:mm") << " : " <<
                      task->completionTime().toString("dd-MM-yyyy hh:mm") << "\n";

        for (Task* subtask : task->subtasks())
        {
            fileStream << " - " << subtask->name() << " : " << subtask->status() << "\n";
        }

        fileStream << "\n";
    }

    file.close();
}

TaskTrackerWidget::~TaskTrackerWidget()
{
    saveData();
}
