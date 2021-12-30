#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QMap>
#include <QListWidgetItem>

#include "../ListComponents/taskwidget.h"
#include "../task.h"
#include "../ListComponents/taskwidgetitem.h"
#include "listwidget.h"

class TaskListWidget : public ListWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Repeatable,
        OneTime
    };

    TaskListWidget(TaskListWidget::Type type, QWidget* parent = nullptr);

public slots:
    void showContextMenu(const QPoint& point) override;
    void createDisplayedWidget(Task* task);

signals:
    void taskCreated(Task* task);
    void taskRemoved(Task* task);

private slots:
    void createObject() override;
    void removeObject() override;

private:
    Type m_type;
};

#endif // TASKLISTWIDGET_H
