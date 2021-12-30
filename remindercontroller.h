#ifndef REMINDERCONTROLLER_H
#define REMINDERCONTROLLER_H

#include <QObject>
#include <QTimer>

class ReminderController : public QObject
{
    Q_OBJECT
public:
    explicit ReminderController(QObject *parent = nullptr);
    ~ReminderController();

public slots:
    void setupReminder(int repeatIntervalInMinutes, const QString& header, const QString& message);

signals:
    void reminderCreated(const QString& header, const QString& message);

private:
    QList<QTimer*> m_timers;

    void loadData();
    void saveData();

    struct Reminder
    {
        int repeatIntervalInMinutes;
        QString header;
        QString message;

        Reminder(int repeatIntervalInMinutes, const QString& header, const QString& message)
        {
            this->repeatIntervalInMinutes = repeatIntervalInMinutes;
            this->header = header;
            this->message = message;
        }
    };

    QList<Reminder> m_reminders;
};

#endif // REMINDERCONTROLLER_H
