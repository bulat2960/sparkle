#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "editablelabel.h"
#include "subtaskwidget.h"
#include "../task.h"

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    TaskWidget(Task* task, QWidget* parent = nullptr);
    ~TaskWidget();

    Task* task() const;

public slots:
    void addSubtaskWidget(Task* subtask);
    void removeSubtaskWidget(Task* subtask);

signals:
    void heightChanged(int height);

private slots:
    void setSubtasksVisible(bool checked);

    void onDeadlineButtonClicked();
    void onPeriodicityButtonClicked();
    void onDoneButtonClicked();
    void onPendingButtonClicked();
    void onFailedButtonClicked();

    void updateDeadlineState(const QDateTime& deadline);
    void updatePeriodicityState(const TimeSpan& periodicity);
    void updateCompletionTimeState(const QDateTime& completionTime);

    void changeStatus(Task::Status status);


private:
    QPushButton* m_showSubtasksButton {nullptr};
    QPushButton* m_addSubtaskButton {nullptr};

    EditableLabel* m_editableLabel {nullptr};

    QPushButton* m_deadlineButton {nullptr};

    QPushButton* m_periodicityButton {nullptr};

    QPushButton* m_doneButton {nullptr};
    QPushButton* m_pendingButton {nullptr};
    QPushButton* m_failedButton {nullptr};

    QLabel* m_deadlineLabel {nullptr};
    QLabel* m_periodicityLabel {nullptr};
    QLabel* m_completionTimeLabel {nullptr};

    QVBoxLayout* m_mainLayout {nullptr};

    QList<SubtaskWidget*> m_subtaskWidgetList;
    QMap<Task*, SubtaskWidget*> m_subtaskWidgetMap;

    Task* m_task {nullptr};

    void addEmptySubtask();

    void ensureSubtasksVisible();

    void updateTaskControls();
    void updateSubtasksControls();

    void setupButton(QPushButton* button, const QString& iconName);
};

#endif // TASKWIDGET_H
