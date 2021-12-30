#include "timespan.h"

static const int secondsInMinute = 60;
static const int minutesInHour = 60;
static const int hoursInDay = 24;
static const int daysInWeek = 7;
static const int daysInMonth = 30;
static const int monthsInYear = 12;

TimeSpan::TimeSpan(int timeSpan)
{
    m_timeSpan = timeSpan;
}

TimeSpan& TimeSpan::addSeconds(int seconds)
{
    m_timeSpan += seconds;
    return *this;
}

int TimeSpan::seconds() const
{
    return m_timeSpan;
}

TimeSpan& TimeSpan::addMinutes(int minutes)
{
    m_timeSpan += minutes * secondsInMinute;
    return *this;
}

int TimeSpan::minutes() const
{
    return m_timeSpan / secondsInMinute;
}

TimeSpan& TimeSpan::addHours(int hours)
{
    m_timeSpan += hours * minutesInHour * secondsInMinute;
    return *this;
}

int TimeSpan::hours() const
{
    return m_timeSpan / (minutesInHour * secondsInMinute);
}

TimeSpan& TimeSpan::addDays(int days)
{
    m_timeSpan += days * hoursInDay * minutesInHour * secondsInMinute;
    return *this;
}

int TimeSpan::days() const
{
    return m_timeSpan / (hoursInDay * minutesInHour * secondsInMinute);
}

TimeSpan& TimeSpan::addWeeks(int weeks)
{
    m_timeSpan += weeks * daysInWeek * hoursInDay * minutesInHour * secondsInMinute;
    return * this;
}

int TimeSpan::weeks() const
{
    return m_timeSpan / (daysInWeek * hoursInDay * minutesInHour * secondsInMinute);
}

TimeSpan& TimeSpan::addMonths(int months)
{
    m_timeSpan += months * daysInMonth * hoursInDay * minutesInHour * secondsInMinute;
    return *this;
}

int TimeSpan::months() const
{
    return m_timeSpan / (daysInMonth * hoursInDay * minutesInHour * secondsInMinute);
}

TimeSpan& TimeSpan::addYears(int years)
{
    m_timeSpan += years * monthsInYear * daysInMonth * hoursInDay * minutesInHour * secondsInMinute;
    return *this;
}

int TimeSpan::years() const
{
    return m_timeSpan / (monthsInYear * daysInMonth * hoursInDay * minutesInHour * secondsInMinute);
}

bool TimeSpan::isValid() const
{
    return m_timeSpan > 0;
}

TimeSpan TimeSpan::operator-(const TimeSpan& other)
{
    return TimeSpan(m_timeSpan - other.m_timeSpan);
}

TimeSpan TimeSpan::operator+(const TimeSpan &other)
{
    return TimeSpan(m_timeSpan + other.m_timeSpan);
}

bool TimeSpan::operator==(int value) const
{
    return m_timeSpan == value;
}

bool TimeSpan::operator==(const TimeSpan& other) const
{
    return m_timeSpan == other.m_timeSpan;
}

QString TimeSpan::toString() const
{
    if (m_timeSpan == secondsInMinute)
    {
        return QStringLiteral("minute");
    }
    else if (m_timeSpan == minutesInHour * secondsInMinute)
    {
        return QStringLiteral("hour");
    }
    else if (m_timeSpan == hoursInDay * minutesInHour * secondsInMinute)
    {
        return QStringLiteral("day");
    }
    else if (m_timeSpan == daysInWeek * hoursInDay * minutesInHour * secondsInMinute)
    {
        return QStringLiteral("week");
    }
    else if (m_timeSpan == daysInMonth * hoursInDay * minutesInHour * secondsInMinute)
    {
        return QStringLiteral("month");
    }
    else if (m_timeSpan != 0)
    {
        int remainder = m_timeSpan;

        int months = remainder / (daysInMonth * hoursInDay * minutesInHour * secondsInMinute);
        remainder %= daysInMonth * hoursInDay * minutesInHour * secondsInMinute;

        int weeks = remainder / (daysInWeek * hoursInDay * minutesInHour * secondsInMinute);
        remainder %= daysInWeek * hoursInDay * minutesInHour * secondsInMinute;

        int days = remainder / (hoursInDay * minutesInHour * secondsInMinute);
        remainder %= hoursInDay * minutesInHour * secondsInMinute;

        int hours = remainder / (minutesInHour * secondsInMinute);
        remainder %= minutesInHour * secondsInMinute;

        int minutes = remainder / secondsInMinute;
        remainder %= secondsInMinute;

        int seconds = remainder;

        QList<int> timeList = {months, weeks, days, hours, minutes, seconds};
        QStringList timeStringList = {"months", "weeks", "days", "hours", "minutes", "seconds"};

        bool foundNotNull = false;

        while (not foundNotNull)
        {
            if (timeList.first() == 0)
            {
                timeList.removeFirst();
                timeStringList.removeFirst();
                continue;
            }
            foundNotNull = true;
        }

        foundNotNull = false;

        while (not foundNotNull)
        {
            if (timeList.last() == 0)
            {
                timeList.removeLast();
                timeStringList.removeLast();
                continue;
            }
            foundNotNull = true;
        }

        if (timeList.isEmpty())
        {
            return "";
        }

        if (timeList.size() == 1)
        {
            return QStringLiteral("%1 %2").arg(timeList[0]).arg(timeStringList[0]);
        }

        if (timeList.size() >= 2)
        {
            if (timeList[1] == 0)
            {
                return QStringLiteral("%1 %2").arg(timeList[0]).arg(timeStringList[0]);
            }
            else
            {
                return QStringLiteral("%1 %2 and %3 %4")
                        .arg(timeList[0]).arg(timeStringList[0])
                        .arg(timeList[1]).arg(timeStringList[1]);
            }
        }
    }

    return "";
}

bool TimeSpan::operator<(const TimeSpan& other) const
{
    return m_timeSpan < other.m_timeSpan;
}
