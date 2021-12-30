#ifndef LISTWIDGETITEM_H
#define LISTWIDGETITEM_H

#include <QObject>
#include <QListWidgetItem>
#include <QWidget>

class ListWidgetItem : public QObject, public QListWidgetItem
{
    Q_OBJECT

public:
    ListWidgetItem(QWidget* widget, QListWidget* parent = nullptr);

    bool operator<(const QListWidgetItem& other) const = 0;

public slots:
    void changeSortingOrder(const QString& sotringOrderString);

protected:
    QString m_sortingOrderString;

    QWidget* m_widget {nullptr};
};

#endif // LISTWIDGETITEM_H
