#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QList>
#include <QObject>
#include <QDateTime>

#include "Utility/timespan.h"

class Task : public QObject
{   
    Q_OBJECT

public:
    enum Status : int
    {
        Pending = 1,
        Failed,
        Done
    };

    Task(const QString& name = "",
         int status = Status::Pending,
         const TimeSpan& periodicity = TimeSpan(),
         const QDateTime& deadline = QDateTime(),
         const QDateTime& completionTime = QDateTime(),
         QObject* parent = nullptr);

    void addSubtask(Task* subtask);
    void removeSubtask(Task* subtask);

    QString name() const;
    Status status() const;
    QDateTime deadline() const;
    QDateTime completionTime() const;
    TimeSpan periodicity() const;

    QList<Task*> subtasks() const;

    bool areSubtasksDone() const;
    bool hasDeadline() const;

signals:
    void nameChanged(const QString& name);
    void statusChanged(Task::Status status);
    void deadlineChanged(const QDateTime& deadline);
    void completionTimeChanged(const QDateTime& completionTime);
    void periodicityChanged(const TimeSpan& periodicity);

    void subtaskAdded(Task* subtask);
    void subtaskRemoved(Task* subtask);

public slots:
    void setName(const QString& name);
    void setStatus(Task::Status status);
    void setDeadline(const QDateTime& deadline);
    void setCompletionTime(const QDateTime& completionTime);
    void setPeriodicity(const TimeSpan& periodicity);

private:
    QString m_name;
    Status m_status {Task::Status::Pending};

    QDateTime m_deadline;
    QDateTime m_completionTime;
    TimeSpan m_periodicity;

    QList<Task*> m_subtasks;

};

#endif // TASK_H
