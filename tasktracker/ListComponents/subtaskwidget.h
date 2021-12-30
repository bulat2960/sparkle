#ifndef SUBTASKWIDGET_H
#define SUBTASKWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>

#include "editablelabel.h"
#include "../task.h"

class SubtaskWidget : public QWidget
{
    Q_OBJECT

public:
    SubtaskWidget(Task* task, QWidget* parent = nullptr);

    void setControlsVisible(bool visible);
    void setTaskEditable(bool editable);

signals:
    void subtaskRemoveRequested(Task* subtask);

private slots:
    void changeStatus(Task::Status status);

private:
    EditableLabel* m_editableLabel {nullptr};
    QCheckBox* m_checkBox {nullptr};

    QPushButton* m_removeButton {nullptr};

    Task* m_task {nullptr};
};

#endif // SUBTASKWIDGET_H
