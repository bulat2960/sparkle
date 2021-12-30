#ifndef CREATETASKDIALOG_H
#define CREATETASKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "../task.h"
#include "../Widgets/tasklistwidget.h"

class CreateTaskDialog : public QDialog
{
public:
    CreateTaskDialog(TaskListWidget::Type type, QWidget* parent = nullptr);

    Task* createTask();

private slots:
    void setPeriodicity();
    void setDeadline();

private:
    QLineEdit* m_taskNameLineEdit {nullptr};

    QPushButton* m_setDeadlineButton {nullptr};
    QPushButton* m_setPeriodicityButton {nullptr};

    TimeSpan m_periodicity;
    QDateTime m_deadline;

    TaskListWidget::Type m_type;
};

#endif // CREATETASKDIALOG_H
