#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QStringList>

class Note : public QObject
{
    Q_OBJECT

public:
    Note(const QString& note = QString(),
         const QStringList& categories = QStringList(),
         const QDateTime& lastUpdateDateTime = QDateTime(),
         QObject* parent = nullptr);

    QString note() const;
    QStringList categories() const;
    bool hasCategory(const QString& category) const;

    QDateTime lastUpdateDateTime() const;

public slots:
    void setNote(const QString& note);

    void addCategory(const QString& category);
    void removeCategory(const QString& category);

    void setLastUpdateDateTime(const QDateTime& lastUpdateDateTime);

signals:
    void categoryAdded(const QString& category);
    void categoryRemoved(const QString& category);

private:
    QString m_note;
    QStringList m_categories;

    QDateTime m_lastUpdateDateTime;
};
#endif // NOTE_H
