#include "timercontroller.h"

TimerController::TimerController(QObject* parent) : QObject(parent)
{

}

void TimerController::setupReminder(QTimer* timer, int timeInterval, const std::function<void (void)>& f)
{
    timer->setSingleShot(true);
    timer->setInterval(timeInterval * 1000);
    connect(timer, &QTimer::timeout, this, f);
}

void TimerController::registerPeriodicalTask(Task* task)
{
    unregisterTask(task);

    QDateTime deadline = task->deadline();
    TimeSpan periodicity = task->periodicity();

    if (not periodicity.isValid())
    {
        return;
    }


    int periodicityParts = QDateTime::currentSecsSinceEpoch() / periodicity.seconds();
    periodicityParts++;

    deadline.setSecsSinceEpoch(periodicityParts * periodicity.seconds());
    task->setDeadline(deadline);


    int timeBeforeNearestNotification = deadline.toSecsSinceEpoch() - QDateTime::currentSecsSinceEpoch();

    auto timer = new QTimer(this);

    auto periodicalTaskReminderCallback = [this, timer, task]
    {
        timer->setInterval(task->periodicity().seconds() * 1000);
        timer->start();
        task->setStatus(Task::Status::Pending);
        task->setDeadline(task->deadline().addSecs(task->periodicity().seconds()));
        emit deadlineNotified("Task renewed", task->name());
    };

    setupReminder(timer, timeBeforeNearestNotification, periodicalTaskReminderCallback);

    timer->start();

    m_taskTimerMap.insert(task, timer);
}

void TimerController::registerOneTimeTask(Task* task)
{
    unregisterTask(task);

    QDateTime deadline = task->deadline();

    if (not deadline.isValid() or deadline < QDateTime::currentDateTime() or task->status() == Task::Status::Done)
    {
        return;
    }


    int timeBeforeNotification = deadline.toSecsSinceEpoch() - QDateTime::currentSecsSinceEpoch();

    auto timer = new QTimer(this);

    auto oneTimeTaskReminderCallback = [this, task]
    {
        task->setStatus(Task::Status::Failed);
        emit deadlineNotified("Task failed", task->name());
    };

    setupReminder(timer, timeBeforeNotification, oneTimeTaskReminderCallback);

    timer->start();

    m_taskTimerMap.insert(task, timer);
}

void TimerController::unregisterTask(Task* task)
{
    if (m_taskTimerMap.contains(task))
    {
        m_taskTimerMap[task]->deleteLater();
        m_taskTimerMap.remove(task);
    }
}
