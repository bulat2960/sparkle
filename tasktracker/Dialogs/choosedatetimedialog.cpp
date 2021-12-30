#include "choosedatetimedialog.h"

#include <QHBoxLayout>
#include <QStringListModel>
#include <QMessageBox>
#include <QDialogButtonBox>

ChooseDateTimeDialog::ChooseDateTimeDialog(QWidget* parent) : QDialog(parent)
{
    m_calendarWidget = new QCalendarWidget(this);
    m_calendarWidget->setStyleSheet("QTableView { selection-background-color: yellow; selection-color: black; }");
    m_calendarWidget->setMinimumDate(QDate::currentDate());
    connect(m_calendarWidget, &QCalendarWidget::selectionChanged, this, &ChooseDateTimeDialog::fillTimeList);

    m_timeList = new QListView(this);
    m_timeList->setEditTriggers(QListView::NoEditTriggers);
    m_timeList->setStyleSheet("QListView::item:selected { background-color: yellow; color: black; }");
    fillTimeList();

    auto dateTimeLayout = new QHBoxLayout;
    dateTimeLayout->addWidget(m_calendarWidget, 5);
    dateTimeLayout->addWidget(m_timeList, 1);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &ChooseDateTimeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ChooseDateTimeDialog::reject);

    m_clearDateTimeButton = new QPushButton("Clear datetime");
    connect(m_clearDateTimeButton, &QPushButton::clicked, this, &ChooseDateTimeDialog::clearDateTime);
    m_clearDateTimeButton->hide();

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addLayout(dateTimeLayout);
    m_mainLayout->addWidget(m_clearDateTimeButton);
    m_mainLayout->addWidget(buttonBox);
}

void ChooseDateTimeDialog::showClearDateTimeButton()
{
    m_clearDateTimeButton->show();
}

void ChooseDateTimeDialog::clearDateTime()
{
    m_date = QDate();
    m_time = QTime();
    QDialog::accept();
}

void ChooseDateTimeDialog::fillTimeList()
{
    bool needRemoveTimeStrings = m_calendarWidget->selectedDate() == QDate::currentDate();

    auto model = new QStringListModel;

    QStringList stringList;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            int hours = i;
            int minutes = j * 5;

            if (needRemoveTimeStrings and QTime(hours, minutes) < QTime::currentTime())
            {
                continue;
            }
            stringList.append(QStringLiteral("%1:%2").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')));
        }
    }

    model->setStringList(stringList);

    m_timeList->setModel(model);
}

void ChooseDateTimeDialog::accept()
{      
    m_date = m_calendarWidget->selectedDate();

    QModelIndex index = m_timeList->currentIndex();

    if (not index.isValid())
    {
        QMessageBox::warning(this, "Warning!", "Please choose date and time",
                             QMessageBox::StandardButton::Ok);
        return;
    }

    QString timeString = index.data().toString();
    QStringList dataList = timeString.split(":");
    int hours = dataList[0].toInt();
    int minutes = dataList[1].toInt();
    m_time.setHMS(hours, minutes, 0);

    QDialog::accept();
}

QDateTime ChooseDateTimeDialog::getDateTime() const
{
    return QDateTime(m_date, m_time);
}
