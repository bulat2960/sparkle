#ifndef TASKWIDGETITEM_H
#define TASKWIDGETITEM_H

#include "listwidgetitem.h"

#include "taskwidget.h"

class TaskWidgetItem : public ListWidgetItem
{
    Q_OBJECT

public:
    TaskWidgetItem(TaskWidget* taskWidget, QListWidget* parent = nullptr);

    bool operator<(const QListWidgetItem& other) const override;

    TaskWidget* taskWidget() const;

private:
    TaskWidget* m_taskWidget {nullptr};
};

#endif // TASKWIDGETITEM_H
