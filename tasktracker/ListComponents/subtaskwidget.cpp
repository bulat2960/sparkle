#include "subtaskwidget.h"

#include <QHBoxLayout>

const int lineHeight = 30;

SubtaskWidget::SubtaskWidget(Task* task, QWidget* parent)
    : QWidget(parent),
      m_task(task)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_editableLabel = new EditableLabel(task->name(), this);
    m_editableLabel->setFixedHeight(lineHeight);

    m_checkBox = new QCheckBox(this);
    m_checkBox->setFixedSize(lineHeight, lineHeight);
    m_checkBox->setChecked(task->status() == Task::Status::Done);

    auto spacerWidget = new QWidget(this);
    spacerWidget->setFixedSize(80, lineHeight);

    m_removeButton = new QPushButton(this);
    m_removeButton->setFixedSize(lineHeight, lineHeight);
    m_removeButton->setIcon(QIcon(":/icons/remove.png"));
    m_removeButton->setIconSize(m_removeButton->size());

    layout->addWidget(spacerWidget);
    layout->addWidget(m_removeButton);
    layout->addWidget(m_editableLabel);
    layout->addWidget(m_checkBox);

    changeStatus(task->status());

    // Set task name and update text
    connect(m_editableLabel, &EditableLabel::textChanged, task, &Task::setName);
    connect(task, &Task::nameChanged, m_editableLabel, &EditableLabel::setText);

    // Set task state depending on check box state
    connect(m_checkBox, &QCheckBox::stateChanged, m_task, [this](int state)
    {
        if (state == Qt::Unchecked)
        {
            m_task->setStatus(Task::Status::Pending);
        }
        else if (state == Qt::Checked)
        {
            m_task->setStatus(Task::Status::Done);
        }
    });

    // Request remove subtask from list widget
    connect(m_removeButton, &QPushButton::clicked, this, [this]
    {
        emit subtaskRemoveRequested(m_task);
    });

    // Change editable label color when task status changed
    connect(task, &Task::statusChanged, this, &SubtaskWidget::changeStatus);
}

void SubtaskWidget::setControlsVisible(bool visible)
{
    m_checkBox->setVisible(visible);
    m_removeButton->setVisible(visible);
}

void SubtaskWidget::setTaskEditable(bool editable)
{
    m_editableLabel->setEditable(editable);
}

void SubtaskWidget::changeStatus(Task::Status status)
{
    QString color;

    switch (status)
    {
        case Task::Status::Pending:
            color = "yellow";
            break;
        case Task::Status::Done:
            color = "greenyellow";
            break;
        case Task::Status::Failed:
            break;
    }

    m_checkBox->setChecked(m_task->status() == Task::Status::Done);
    m_editableLabel->setColor(color);
}
