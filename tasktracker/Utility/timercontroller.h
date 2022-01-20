#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QTimer>
#include <QObject>
#include <QMap>

#include <functional>

#include "../task.h"

class TimerController : public QObject
{
    Q_OBJECT

public:
    TimerController(QObject* parent = nullptr);

public slots:
    void registerPeriodicalTask(Task* task);
    void registerOneTimeTask(Task* task);
    void unregisterTask(Task* task);

signals:
    void deadlineNotified(const QString& title, const QString& messages);

private:
    QMap<Task*, QTimer*> m_taskTimerMap;

    void setupReminder(QTimer* timer, int timeInterval, const std::function<void (void)>& f);
};

#endif // TIMERCONTROLLER_H
