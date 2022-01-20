#include "remindercontroller.h"

#include <QFile>
#include <QApplication>
#include <QTextStream>

ReminderController::ReminderController(QObject* parent) : QObject(parent)
{
    loadData();
}

void ReminderController::setupReminder(int repeatIntervalInMinutes, const QString& header, const QString& message)
{
    m_reminders.append(Reminder(repeatIntervalInMinutes, header, message));

    auto timer = new QTimer(this);
    timer->setInterval(1000 * 60 * repeatIntervalInMinutes);
    timer->setSingleShot(false);
    timer->start();

    connect(timer, &QTimer::timeout, this, [this, header, message]
    {
        emit reminderCreated(header, message);
    });
}

void ReminderController::loadData()
{
    QFile file(QApplication::applicationDirPath() + "/data/reminders.txt");

    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to load reminders";
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

        setupReminder(data[0].toInt(), data[1], data[2]);
    }

    file.close();
}

void ReminderController::saveData()
{
    QFile file(QApplication::applicationDirPath() + "/data/reminders.txt");

    if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to save reminders";
        return;
    }

    QTextStream fileStream(&file);

    for (const Reminder& reminder : m_reminders)
    {
        fileStream << reminder.repeatIntervalInMinutes << " : " << reminder.header << " : " << reminder.message << "\n";
    }

    file.close();
}

ReminderController::~ReminderController()
{
    saveData();
}
