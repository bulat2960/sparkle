#include "createtaskdialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include "choosedatetimedialog.h"
#include "chooseperiodicitydialog.h"

CreateTaskDialog::CreateTaskDialog(TaskListWidget::Type type, QWidget* parent)
    : QDialog(parent),
      m_type(type)
{
    setMinimumWidth(250);

    m_taskNameLineEdit = new QLineEdit(this);

    auto inputTaskNameLayout = new QHBoxLayout;
    inputTaskNameLayout->addWidget(new QLabel("Task name:"), 1);
    inputTaskNameLayout->addWidget(m_taskNameLineEdit, 4);

    auto acceptButton = new QPushButton("Create");
    acceptButton->setDisabled(true);
    connect(m_taskNameLineEdit, &QLineEdit::textChanged, acceptButton, [acceptButton](const QString& text)
    {
        acceptButton->setEnabled(not text.isEmpty());
    });

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, this);
    buttonBox->addButton(acceptButton, QDialogButtonBox::AcceptRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateTaskDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CreateTaskDialog::reject);


    QPushButton* controlButton = nullptr;

    if (type == TaskListWidget::Type::OneTime)
    {
        controlButton = new QPushButton("Set deadline");
        connect(controlButton, &QPushButton::clicked, this, &CreateTaskDialog::setDeadline);
    }
    else
    {
        controlButton  = new QPushButton("Set periodicity");
        connect(controlButton, &QPushButton::clicked, this, &CreateTaskDialog::setPeriodicity);
    }

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputTaskNameLayout);
    mainLayout->addWidget(controlButton);
    mainLayout->addWidget(buttonBox);
}

void CreateTaskDialog::setDeadline()
{
    if (m_taskNameLineEdit->text().isEmpty())
    {
        QMessageBox box;
        box.setText("Please enter new task name");
        box.exec();
        return;
    }

    ChooseDateTimeDialog dialog(this);
    int code = dialog.exec();

    if (code == QDialog::Accepted)
    {
        m_deadline = dialog.getDateTime();
        QDialog::accept();
    }
}

void CreateTaskDialog::setPeriodicity()
{
    if (m_taskNameLineEdit->text().isEmpty())
    {
        QMessageBox box;
        box.setText("Please enter new task name");
        box.exec();
        return;
    }

    ChoosePeriodicityDialog dialog(this);
    int code = dialog.exec();

    if (code == QDialog::Accepted)
    {
        m_periodicity = dialog.periodicity();
        QDialog::accept();
    }
}

Task* CreateTaskDialog::createTask()
{
    if (m_type == TaskListWidget::Type::Repeatable and not m_periodicity.isValid())
    {
        m_periodicity = TimeSpan().addDays(1);
    }

    return new Task(m_taskNameLineEdit->text(), Task::Status::Pending, m_periodicity, m_deadline);
}
