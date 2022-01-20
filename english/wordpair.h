#ifndef WORDPAIR_H
#define WORDPAIR_H

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QObject>

class WordPair : public QObject
{
    Q_OBJECT

public:
    WordPair(const QString& englishWord = QString(),
             const QString& russianWord = QString(),
             const QStringList& categories = QStringList(),
             double learningQuality = 0,
             const QDateTime& lastLearningTime = QDateTime(),
             QObject* parent = nullptr);

    QString englishWord() const;
    QString russianWord() const;

    QStringList categories() const;
    bool hasCategory(const QString& category) const;

    double learningQuality() const;

    QDateTime lastLearningTime() const;

public slots:
    void setEnglishWord(const QString& englishWord);
    void setRussianWord(const QString& russianWord);

    void setLearningQuality(double learningQuality);

    void setLastLearningTime(const QDateTime& lastLearningTime);

    void addCategory(const QString& category);
    void removeCategory(const QString& category);

signals:
    void categoryAdded(const QString& category);
    void categoryRemoved(const QString& category);
    void learningQualityChanged(double learningQuality);

private:
    QString m_englishWord;
    QString m_russianWord;

    QStringList m_categories;
    double m_learningQuality;

    QDateTime m_lastLearningTime;
};

#endif // WORDPAIR_H
