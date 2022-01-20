#include "chooseperiodicitydialog.h"

#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>

ChoosePeriodicityDialog::ChoosePeriodicityDialog(QWidget* parent) : QDialog(parent)
{

    auto spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_acceptButton = new QPushButton("Accept", this);
    m_rejectButton = new QPushButton("Reject", this);

    auto buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(m_acceptButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(m_rejectButton, QDialogButtonBox::RejectRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ChoosePeriodicityDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ChoosePeriodicityDialog::reject);

    setupRadioButtonsLayout();
    setupCustomPeriodicityLayout();

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_periodicityGroupBox);
    m_mainLayout->addWidget(m_customPeriodicityWidget);
    m_mainLayout->addWidget(buttonBox);
}

void ChoosePeriodicityDialog::changeCustomPeriodicityLayoutVisibility(QAbstractButton* button)
{
    if (button == m_customButton)
    {
        m_customPeriodicityWidget->setEnabled(true);
    }
    else
    {
        m_customPeriodicityWidget->setEnabled(false);
    }
}

void ChoosePeriodicityDialog::setupRadioButtonsLayout()
{
    m_periodicityGroupBox = new QGroupBox("Choose periodicity", this);

    m_hourButton = new QRadioButton("Hourly", this);
    m_dayButton = new QRadioButton("Daily", this);
    m_weekButton = new QRadioButton("Weekly", this);

    m_customButton = new QRadioButton("Custom", this);
    connect(m_customButton, &QRadioButton::clicked, this, [this](bool checked)
    {
        m_acceptButton->setEnabled(not checked);
        if (checked)
        {
            checkCorrectPeriodicity();
        }
    });

    m_hourButton->setChecked(true);

    m_buttonGroup = new QButtonGroup(this);
    connect(m_buttonGroup, &QButtonGroup::buttonClicked, this, &ChoosePeriodicityDialog::changeCustomPeriodicityLayoutVisibility);

    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(m_hourButton);
    m_buttonGroup->addButton(m_dayButton);
    m_buttonGroup->addButton(m_weekButton);
    m_buttonGroup->addButton(m_customButton);

    auto controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(m_hourButton);
    controlsLayout->addWidget(m_dayButton);
    controlsLayout->addWidget(m_weekButton);
    controlsLayout->addWidget(m_customButton);

    m_periodicityGroupBox->setLayout(controlsLayout);

    checkCorrectPeriodicity();
}

void ChoosePeriodicityDialog::setupCustomPeriodicityLayout()
{
    m_customPeriodicityWidget = new QWidget(this);

    auto customPeriodicityLayout = new QGridLayout;

    m_minuteComboBox = new QComboBox(this);
    setupComboBox(m_minuteComboBox, 60);

    m_hourComboBox = new QComboBox(this);
    setupComboBox(m_hourComboBox, 24);

    m_dayComboBox = new QComboBox(this);
    setupComboBox(m_dayComboBox, 30);

    m_weekComboBox = new QComboBox(this);
    setupComboBox(m_weekComboBox, 10);

    m_monthComboBox = new QComboBox(this);
    setupComboBox(m_monthComboBox, 5);

    customPeriodicityLayout->addWidget(new QLabel("Minutes:", this), 0, 0);
    customPeriodicityLayout->addWidget(m_minuteComboBox, 0, 1);

    customPeriodicityLayout->addWidget(new QLabel("Hours:", this), 1, 0);
    customPeriodicityLayout->addWidget(m_hourComboBox, 1, 1);

    customPeriodicityLayout->addWidget(new QLabel("Days:", this), 2, 0);
    customPeriodicityLayout->addWidget(m_dayComboBox, 2, 1);

    customPeriodicityLayout->addWidget(new QLabel("Weeks:", this), 3, 0);
    customPeriodicityLayout->addWidget(m_weekComboBox, 3, 1);

    customPeriodicityLayout->addWidget(new QLabel("Months:", this), 4, 0);
    customPeriodicityLayout->addWidget(m_monthComboBox, 4, 1);

    m_customPeriodicityWidget->setLayout(customPeriodicityLayout);
    m_customPeriodicityWidget->setEnabled(false);
}

void ChoosePeriodicityDialog::setupComboBox(QComboBox* comboBox, int maxValue)
{
    for (int i = 0; i < maxValue; i++)
    {
        comboBox->addItem(QString::number(i));
    }
    connect(comboBox, &QComboBox::currentIndexChanged, this, &ChoosePeriodicityDialog::checkCorrectPeriodicity);
}

TimeSpan ChoosePeriodicityDialog::periodicity() const
{
    return m_periodicity;
}

void ChoosePeriodicityDialog::checkCorrectPeriodicity()
{
    auto checkedButton = static_cast<QRadioButton*>(m_buttonGroup->checkedButton());

    if (checkedButton == m_customButton)
    {
        int minutes = m_minuteComboBox->currentIndex();
        int hours = m_hourComboBox->currentIndex();
        int days = m_dayComboBox->currentIndex();
        int weeks = m_weekComboBox->currentIndex();
        int months = m_monthComboBox->currentIndex();

        m_acceptButton->setEnabled((minutes + hours + days + weeks + months) != 0);
    }
}

void ChoosePeriodicityDialog::accept()
{
    auto checkedButton = static_cast<QRadioButton*>(m_buttonGroup->checkedButton());

    if (checkedButton == nullptr)
    {
        return;
    }

    if (checkedButton == m_hourButton)
    {
        m_periodicity = TimeSpan().addHours(1);
    }
    else if (checkedButton == m_dayButton)
    {
        m_periodicity = TimeSpan().addDays(1);
    }
    else if (checkedButton == m_weekButton)
    {
        m_periodicity = TimeSpan().addWeeks(1);
    }
    else if (checkedButton == m_customButton)
    {
        int minutes = m_minuteComboBox->currentIndex();
        int hours = m_hourComboBox->currentIndex();
        int days = m_dayComboBox->currentIndex();
        int weeks = m_weekComboBox->currentIndex();
        int months = m_monthComboBox->currentIndex();

        m_periodicity = TimeSpan().addMinutes(minutes).addHours(hours).addDays(days).addWeeks(weeks).addMonths(months);
    }

    QDialog::accept();
}
