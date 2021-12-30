#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <QDateTime>


class TimeSpan
{
public:
    TimeSpan() = default;
    TimeSpan(int timeSpan);

    TimeSpan& addSeconds(int seconds);
    TimeSpan& addMinutes(int minutes);
    TimeSpan& addHours(int hours);

    TimeSpan& addDays(int days);
    TimeSpan& addWeeks(int weeks);
    TimeSpan& addMonths(int months);
    TimeSpan& addYears(int years);

    int seconds() const;
    int minutes() const;
    int hours() const;

    int days() const;
    int weeks() const;
    int months() const;
    int years() const;

    bool isValid() const;

    static TimeSpan between(const QDateTime& firstDateTime, const QDateTime& secondDateTime);

    TimeSpan operator-(const TimeSpan& other);
    TimeSpan operator+(const TimeSpan& other);
    bool operator==(int value) const;
    bool operator==(const TimeSpan& other) const;

    bool operator<(const TimeSpan& other) const;

    QString toString() const;

private:
    int m_timeSpan {0};
};

#endif // TIMESPAN_H
