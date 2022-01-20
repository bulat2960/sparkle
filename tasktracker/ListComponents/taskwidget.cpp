#include "taskwidget.h"

#include <QHBoxLayout>
#include <QCheckBox>
#include <QMessageBox>

#include "../Dialogs/choosedatetimedialog.h"
#include "../Dialogs/chooseperiodicitydialog.h"

static const int headerHeight = 50;
static const int statusLabelHeight = 25;
static const int statusLabelsSpacing = 10;
static const int subtaskHeight = 30;

TaskWidget::TaskWidget(Task* task, QWidget* parent)
    : QWidget(parent),
      m_task(task)
{   
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_mainLayout->setSpacing(10);

    auto labelsLayout = new QVBoxLayout;
    labelsLayout->setContentsMargins(0, 0, 0, 0);
    labelsLayout->setSpacing(statusLabelsSpacing);

    auto statusLabelsLayout = new QHBoxLayout;
    statusLabelsLayout->setContentsMargins(0, 0, 0, 0);
    statusLabelsLayout->setSpacing(5);

    m_editableLabel = new EditableLabel(task->name(), this);
    m_editableLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_editableLabel->setMinimumWidth(headerHeight);
    m_editableLabel->setFixedHeight(headerHeight);

    m_deadlineLabel = new QLabel(this);
    m_deadlineLabel->setFixedHeight(statusLabelHeight);

    updateDeadlineState(task->deadline());
    connect(task, &Task::deadlineChanged, this, &TaskWidget::updateDeadlineState);

    m_periodicityLabel = new QLabel(this);
    m_periodicityLabel->setFixedHeight(statusLabelHeight);

    updatePeriodicityState(task->periodicity());
    connect(task, &Task::periodicityChanged, this, &TaskWidget::updatePeriodicityState);

    m_completionTimeLabel = new QLabel(this);
    m_completionTimeLabel->setFixedHeight(statusLabelHeight);

    updateCompletionTimeState(task->completionTime());
    connect(task, &Task::completionTimeChanged, this, &TaskWidget::updateCompletionTimeState);

    auto spacerLabel = new QLabel(this);
    spacerLabel->setFixedHeight(statusLabelHeight);

    statusLabelsLayout->addWidget(m_deadlineLabel);
    statusLabelsLayout->addWidget(m_periodicityLabel);
    statusLabelsLayout->addWidget(m_completionTimeLabel);
    statusLabelsLayout->addWidget(spacerLabel, 100);

    labelsLayout->addWidget(m_editableLabel, 3);
    labelsLayout->addLayout(statusLabelsLayout, 2);

    auto controlsLayout = new QHBoxLayout;
    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(5);

    m_showSubtasksButton = new QPushButton(this);
    setupButton(m_showSubtasksButton, "bullet_arrow_right");
    m_showSubtasksButton->setCheckable(true);
    m_showSubtasksButton->setChecked(false);

    m_addSubtaskButton = new QPushButton(this);
    setupButton(m_addSubtaskButton, "add");

    m_deadlineButton = new QPushButton(this);
    setupButton(m_deadlineButton, "deadline");

    m_periodicityButton = new QPushButton(this);
    setupButton(m_periodicityButton, "periodicity");

    m_doneButton = new QPushButton(this);
    setupButton(m_doneButton, "check");

    m_failedButton = new QPushButton(this);
    setupButton(m_failedButton, "cross");

    m_pendingButton = new QPushButton(this);
    setupButton(m_pendingButton, "pending");

    controlsLayout->addWidget(m_showSubtasksButton);
    controlsLayout->addWidget(m_addSubtaskButton);
    controlsLayout->addLayout(labelsLayout);
    controlsLayout->addWidget(m_deadlineButton);
    controlsLayout->addWidget(m_periodicityButton);
    controlsLayout->addWidget(m_doneButton);
    controlsLayout->addWidget(m_pendingButton);
    controlsLayout->addWidget(m_failedButton);

    m_mainLayout->addLayout(controlsLayout);

    for (auto subtask : task->subtasks())
    {
        addSubtaskWidget(subtask);
    }

    changeStatus(m_task->status());
    ensureSubtasksVisible();

    if (not task->periodicity().isValid())
    {
        m_periodicityLabel->hide();
        m_periodicityButton->hide();
    }

    // Connections on task status change buttons
    connect(m_deadlineButton, &QPushButton::clicked, this, &TaskWidget::onDeadlineButtonClicked);
    connect(m_periodicityButton, &QPushButton::clicked, this, &TaskWidget::onPeriodicityButtonClicked);
    connect(m_doneButton, &QPushButton::clicked, this, &TaskWidget::onDoneButtonClicked);
    connect(m_failedButton, &QPushButton::clicked, this, &TaskWidget::onFailedButtonClicked);
    connect(m_pendingButton, &QPushButton::clicked, this, &TaskWidget::onPendingButtonClicked);

    // Show subtasks layout
    connect(m_showSubtasksButton, &QPushButton::toggled, this, &TaskWidget::setSubtasksVisible);
    connect(m_addSubtaskButton, &QPushButton::clicked, this, &TaskWidget::addEmptySubtask);
    connect(m_editableLabel, &EditableLabel::textChanged, task, &Task::setName);

    // Change task status connection
    connect(m_task, &Task::statusChanged, this, &TaskWidget::changeStatus);

    // Show add subtask button if widget is interactive
    connect(m_showSubtasksButton, &QPushButton::toggled, m_addSubtaskButton, [this]
    {
        m_addSubtaskButton->setVisible(m_showSubtasksButton->isChecked() and m_task->status() == Task::Status::Pending);
    });
}

void TaskWidget::updateDeadlineState(const QDateTime& deadline)
{
    if (not deadline.isValid())
    {
        m_deadlineLabel->hide();
    }
    else
    {
        if (m_task->periodicity().isValid())
        {
            m_deadlineLabel->setText(QStringLiteral("📆 Next update: %1").arg(deadline.toString("dd.MM.yy hh:mm:ss")));
        }
        else
        {
            m_deadlineLabel->setText(QStringLiteral("📆 Until %1").arg(deadline.toString("dd.MM.yy hh:mm:ss")));
        }
        m_deadlineLabel->show();
    }
}

void TaskWidget::updatePeriodicityState(const TimeSpan& periodicity)
{
    if (not periodicity.isValid())
    {
        m_periodicityLabel->hide();
    }
    else
    {
        m_periodicityLabel->setText(QStringLiteral("⏳ Every %1").arg(periodicity.toString()));
        m_periodicityLabel->show();
    }
}

void TaskWidget::updateCompletionTimeState(const QDateTime& completionTime)
{
    if (not completionTime.isValid())
    {
        m_completionTimeLabel->hide();
    }
    else
    {
        m_completionTimeLabel->setText(QStringLiteral("✅ Completed %1").arg(completionTime.toString("dd.MM.yy hh:mm:ss")));
        m_completionTimeLabel->show();
    }
}

Task* TaskWidget::task() const
{
    return m_task;
}

void TaskWidget::setupButton(QPushButton* button, const QString& iconName)
{
    button->setFixedSize(headerHeight + statusLabelHeight + statusLabelsSpacing, headerHeight + statusLabelHeight + statusLabelsSpacing);
    button->setIcon(QIcon(QStringLiteral(":/icons/%1.png").arg(iconName)));
    button->setIconSize(button->size());
}

void TaskWidget::ensureSubtasksVisible()
{
    int marginsHeight = m_mainLayout->contentsMargins().top() + m_mainLayout->contentsMargins().bottom();
    int subtasksLayoutHeight = (subtaskHeight + m_mainLayout->spacing()) * m_subtaskWidgetList.size();

    if (not m_showSubtasksButton->isChecked())
    {
        subtasksLayoutHeight = 0;
    }

    int height = headerHeight + statusLabelHeight + statusLabelsSpacing + marginsHeight + subtasksLayoutHeight;

    emit heightChanged(height);
}

void TaskWidget::updateTaskControls()
{
    m_deadlineButton->setVisible(m_task->status() == Task::Status::Pending and not m_task->periodicity().isValid());
    m_periodicityButton->setVisible(m_task->status() == Task::Status::Pending and m_task->periodicity().isValid());
    m_doneButton->setVisible(m_task->status() == Task::Status::Pending);
    m_pendingButton->setVisible(m_task->status() != Task::Status::Pending);
    m_failedButton->setVisible(m_task->status() == Task::Status::Pending);
    m_addSubtaskButton->setVisible(m_task->status() == Task::Status::Pending and m_showSubtasksButton->isChecked());
    m_editableLabel->setEditable(m_task->status() == Task::Status::Pending);

    updateSubtasksControls();
}

void TaskWidget::updateSubtasksControls()
{
    for (auto subtaskWidget : m_subtaskWidgetList)
    {
        subtaskWidget->setControlsVisible(m_task->status() == Task::Status::Pending);
        subtaskWidget->setTaskEditable(m_task->status() == Task::Status::Pending);
    }
}

void TaskWidget::setSubtasksVisible(bool checked)
{
    for (auto subtaskWidget : m_subtaskWidgetList)
    {
        subtaskWidget->setVisible(checked);
    }

    m_showSubtasksButton->setIcon(QIcon(QStringLiteral(":/icons/bullet_arrow_%1.png").arg(checked ? "down" : "right")));

    ensureSubtasksVisible();
}

void TaskWidget::addSubtaskWidget(Task* subtask)
{
    auto subtaskWidget = new SubtaskWidget(subtask, this);

    subtaskWidget->setVisible(m_showSubtasksButton->isChecked());

    m_subtaskWidgetList.append(subtaskWidget);
    m_subtaskWidgetMap.insert(subtask, subtaskWidget);

    m_mainLayout->addWidget(subtaskWidget);

    ensureSubtasksVisible();

    // Remove task when corresponding widget is about to be destroyed
    connect(subtaskWidget, &SubtaskWidget::subtaskRemoveRequested, m_task, &Task::removeSubtask);
}

void TaskWidget::removeSubtaskWidget(Task* subtask)
{
    auto subtaskWidget = m_subtaskWidgetMap[subtask];
    m_subtaskWidgetList.removeOne(subtaskWidget);
    m_subtaskWidgetMap.remove(subtask);

    m_mainLayout->removeWidget(subtaskWidget);
    subtaskWidget->deleteLater();

    ensureSubtasksVisible();
}

void TaskWidget::addEmptySubtask()
{
    Task* subtask = new Task;
    m_task->addSubtask(subtask);
}

void TaskWidget::onDeadlineButtonClicked()
{
    ChooseDateTimeDialog dialog(this);

    if (m_task->hasDeadline())
    {
        dialog.showClearDateTimeButton();
    }

    int result = dialog.exec();

    if (result == QDialog::Accepted)
    {
        QDateTime deadline = dialog.getDateTime();
        m_task->setDeadline(deadline);
    }
}

void TaskWidget::onPeriodicityButtonClicked()
{
    ChoosePeriodicityDialog dialog;

    int result = dialog.exec();

    if (result == QDialog::Accepted)
    {
        TimeSpan periodicity = dialog.periodicity();
        m_task->setPeriodicity(periodicity);
    }
}

void TaskWidget::onDoneButtonClicked()
{
    bool subtasksDone = m_task->areSubtasksDone();

    if (not subtasksDone)
    {
        QMessageBox::warning(this,
                             "Warning!",
                             "Subtasks are not finished.\nPlease finish subtasks before you can mark this task as done.");
        return;
    }

    m_task->setCompletionTime(QDateTime::currentDateTime());
    m_task->setStatus(Task::Status::Done);
}

void TaskWidget::onPendingButtonClicked()
{
    for (Task* subtask : m_task->subtasks())
    {
        subtask->setStatus(Task::Status::Pending);
    }

    m_task->setStatus(Task::Status::Pending);
}

void TaskWidget::onFailedButtonClicked()
{
    for (Task* subtask : m_task->subtasks())
    {
        subtask->setStatus(Task::Status::Pending);
    }

    m_task->setStatus(Task::Status::Failed);
}

void TaskWidget::changeStatus(Task::Status status)
{
    QMap<Task::Status, QString> statusColor = {
        {Task::Status::Pending, "yellow"},
        {Task::Status::Done, "greenyellow"},
        {Task::Status::Failed, "orangered"}
    };

    m_editableLabel->setColor(statusColor[status]);

    updateTaskControls();
}
