#include "task.h"

Task::Task(const QString& name, int status, const TimeSpan& periodicity,
           const QDateTime& deadline, const QDateTime& completionTime,
           QObject *parent)
    : QObject(parent)
{
    m_name = name;
    m_status = static_cast<Status>(status);
    m_periodicity = periodicity;
    m_deadline = deadline;
    m_completionTime = completionTime;
}

void Task::addSubtask(Task* subtask)
{
    m_subtasks.append(subtask);
    emit subtaskAdded(subtask);
}

void Task::removeSubtask(Task* subtask)
{
    m_subtasks.removeOne(subtask);
    emit subtaskRemoved(subtask);
}

void Task::setName(const QString& name)
{
    m_name = name;
    emit nameChanged(m_name);
}

QString Task::name() const
{
    return m_name;
}

void Task::setStatus(Status status)
{
    m_status = status;
    emit statusChanged(m_status);

    if (status == Status::Done)
    {
        setCompletionTime(QDateTime::currentDateTime());
    }
    else
    {
        setCompletionTime(QDateTime());
    }
}

Task::Status Task::status() const
{
    return m_status;
}

void Task::setDeadline(const QDateTime& deadline)
{
    m_deadline = deadline;
    emit deadlineChanged(m_deadline);
}

QDateTime Task::deadline() const
{
    return m_deadline;
}

void Task::setPeriodicity(const TimeSpan& periodicity)
{
    m_periodicity = periodicity;
    setDeadline(QDateTime::currentDateTime().addSecs(periodicity.seconds()));
    emit periodicityChanged(m_periodicity);
}

TimeSpan Task::periodicity() const
{
    return m_periodicity;
}

void Task::setCompletionTime(const QDateTime& completionTime)
{
    m_completionTime = completionTime;
    emit completionTimeChanged(m_completionTime);
}

QDateTime Task::completionTime() const
{
    return m_completionTime;
}

QList<Task*> Task::subtasks() const
{
    return m_subtasks;
}

bool Task::areSubtasksDone() const
{
    for (Task* subtask : m_subtasks)
    {
        if (subtask->status() != Task::Status::Done)
        {
            return false;
        }
    }

    return true;
}

bool Task::hasDeadline() const
{
    return m_deadline.isValid();
}
