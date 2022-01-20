#include "mainwindow.h"

const int hideButtonSize = 50;

#include <QTimer>

MainWindow::MainWindow()
{
    m_mainLayout = new QVBoxLayout(this);

    //setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    setWindowIcon(QIcon(":/icons/sparkle.png"));
    setWindowTitle(QStringLiteral("Sparkle"));

    setupControlLayout();
    setupStackedLayout();

    setFocus();

    m_popupController = new PopupController(this);
    connect(m_taskTrackerWidget, &TaskTrackerWidget::popupCreateRequested, m_popupController, &PopupController::createPopup);

    m_reminderController = new ReminderController(this);
    connect(m_reminderController, &ReminderController::reminderCreated, m_popupController, &PopupController::createPopup);
}

void MainWindow::setupControlLayout()
{
    m_minimizeButton = new QPushButton;
    m_minimizeButton->setFixedSize(hideButtonSize, hideButtonSize);
    m_minimizeButton->setIconSize(QSize(hideButtonSize, hideButtonSize));
    m_minimizeButton->setIcon(QIcon(":/icons/close_black.png"));
    connect(m_minimizeButton, &QPushButton::clicked, this, &MainWindow::hide);

    m_currentTimeLabel = new QLabel(QTime::currentTime().toString("hh:mm:ss"), this);
    m_currentTimeLabel->setObjectName("currentTimeLabel");
    m_currentTimeLabel->setAlignment(Qt::AlignVCenter);

    auto timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    timer->setSingleShot(false);
    timer->setInterval(1000);
    timer->start();
    connect(timer, &QTimer::timeout, m_currentTimeLabel, [this]
    {
        m_currentTimeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    });

    m_chooseActivityBox = new QComboBox;
    m_chooseActivityBox->setMinimumWidth(500);
    m_chooseActivityBox->addItems({"English training", "Tasktracker", "Notes", "Spendings"});
    connect(m_chooseActivityBox, &QComboBox::currentIndexChanged, this, &MainWindow::changeActiveWidget);

    m_controlLayout = new QHBoxLayout;
    m_controlLayout->addWidget(m_chooseActivityBox, 10, Qt::AlignLeft);
    m_controlLayout->addWidget(m_currentTimeLabel, 0, Qt::AlignRight);
    m_controlLayout->addWidget(m_minimizeButton, 0, Qt::AlignRight);

    m_mainLayout->addLayout(m_controlLayout);
}

void MainWindow::setupStackedLayout()
{
    m_stackedLayout = new QStackedLayout;

    m_englishWidget = new EnglishWidget(this);
    m_stackedLayout->addWidget(m_englishWidget);

    m_taskTrackerWidget = new TaskTrackerWidget(this);
    m_stackedLayout->addWidget(m_taskTrackerWidget);

    m_notesWidget = new NotesWidget(this);
    m_stackedLayout->addWidget(m_notesWidget);

    m_spendingsWidget = new SpendingsWidget(this);
    m_stackedLayout->addWidget(m_spendingsWidget);

    m_mainLayout->addLayout(m_stackedLayout);
}

void MainWindow::changeActiveWidget()
{
    m_stackedLayout->setCurrentIndex(m_chooseActivityBox->currentIndex());
}

void MainWindow::save()
{
    m_taskTrackerWidget->saveData();
}
