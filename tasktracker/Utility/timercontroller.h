#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QTimer>
#include <QObject>
#include <QMap>

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
    void deadlineNotified(Task* task);

private:
    QMap<Task*, QTimer*> m_taskTimerMap;
};

#endif // TIMERCONTROLLER_H
