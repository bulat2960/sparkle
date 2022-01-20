#include "note.h"

Note::Note(const QString& note,
           const QStringList& categories,
           const QDateTime& lastUpdateDateTime,
           QObject* parent)
    : QObject(parent)
{
    m_note = note;
    m_categories = categories;
    m_lastUpdateDateTime = lastUpdateDateTime;
}

QString Note::note() const
{
    return m_note;
}

QStringList Note::categories() const
{
    return m_categories;
}

bool Note::hasCategory(const QString& category) const
{
    return m_categories.contains(category);
}

QDateTime Note::lastUpdateDateTime() const
{
    return m_lastUpdateDateTime;
}

void Note::setNote(const QString& note)
{
    m_note = note;
}

void Note::addCategory(const QString& category)
{
    if (m_categories.contains(category))
    {
        return;
    }

    m_categories.append(category);
    emit categoryAdded(category);
}

void Note::removeCategory(const QString& category)
{
    if (not m_categories.contains(category))
    {
        return;
    }

    m_categories.removeOne(category);
    emit categoryRemoved(category);
}

void Note::setLastUpdateDateTime(const QDateTime& lastUpdateDateTime)
{
    m_lastUpdateDateTime = lastUpdateDateTime;
}
