#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QAction>
#include <QListWidgetItem>

#include "listwidgetitem.h"

class ListWidget : public QListWidget
{
    Q_OBJECT

public slots:
    virtual void showContextMenu(const QPoint& point) = 0;

    QAction* createSortingRequestAction(const QString& text, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);

    void sort();

public:
    ListWidget(QWidget* parent = nullptr);
    virtual ~ListWidget() = default;

signals:
    void sortingOrderChangeRequested(const QString& type);

protected slots:
    virtual void createObject() = 0;
    virtual void removeObject() = 0;

protected:
    void mousePressEvent(QMouseEvent* event) override;

    ListWidgetItem* m_lastClickedItem {nullptr};
};

#endif // LISTWIDGET_H
