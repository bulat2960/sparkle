#include "wordpair.h"

WordPair::WordPair(const QString& englishWord,
                   const QString& russianWord,
                   const QStringList& categories,
                   double learningQuality,
                   const QDateTime& lastLearningTime,
                   QObject* parent)
    : QObject(parent)
{
    m_englishWord = englishWord;
    m_russianWord = russianWord;
    m_categories = categories;
    m_learningQuality = learningQuality;
    m_lastLearningTime = lastLearningTime;
}

QString WordPair::englishWord() const
{
    return m_englishWord;
}

QString WordPair::russianWord() const
{
    return m_russianWord;
}

QStringList WordPair::categories() const
{
    return m_categories;
}

bool WordPair::hasCategory(const QString& category) const
{
    return m_categories.contains(category);
}

double WordPair::learningQuality() const
{
    return m_learningQuality;
}

QDateTime WordPair::lastLearningTime() const
{
    return m_lastLearningTime;
}

void WordPair::setEnglishWord(const QString& englishWord)
{
    m_englishWord = englishWord;
}

void WordPair::setRussianWord(const QString& russianWord)
{
    m_russianWord = russianWord;
}

void WordPair::addCategory(const QString& category)
{
    if (m_categories.contains(category))
    {
        return;
    }

    m_categories.append(category);
    emit categoryAdded(category);
}

void WordPair::removeCategory(const QString& category)
{
    if (not m_categories.contains(category))
    {
        return;
    }

    m_categories.removeOne(category);
    emit categoryRemoved(category);
}

void WordPair::setLearningQuality(double learningQuality)
{
    m_learningQuality = learningQuality;
    emit learningQualityChanged(learningQuality);
}

void WordPair::setLastLearningTime(const QDateTime& lastLearningTime)
{
    m_lastLearningTime = lastLearningTime;
}
