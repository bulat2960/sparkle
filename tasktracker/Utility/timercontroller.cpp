#include "timercontroller.h"

TimerController::TimerController(QObject* parent) : QObject(parent)
{

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
    timer->setSingleShot(true);
    timer->setInterval(timeBeforeNearestNotification * 1000);
    timer->start();

    connect(timer, &QTimer::timeout, this, [timer, task]
    {
        timer->setInterval(task->periodicity().seconds() * 1000);
        timer->start();
        task->setStatus(Task::Status::Pending);
        task->setDeadline(task->deadline().addSecs(task->periodicity().seconds()));
    });

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
    timer->setSingleShot(true);
    timer->setInterval(timeBeforeNotification * 1000);
    timer->start();

    connect(timer, &QTimer::timeout, this, [this, task]
    {
        task->setStatus(Task::Status::Failed);
        emit deadlineNotified(task);
    });

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
