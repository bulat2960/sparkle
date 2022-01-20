#include "timedtestwidget.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QRandomGenerator>
#include <QMessageBox>

#include "../Utility/categorycolorselector.h"

static const int answerButtonsNumber = 4;

TimedTestWidget::TimedTestWidget(QWidget *parent) : QWidget(parent)
{
    m_stackedLayout = new QStackedLayout(this);

    setupSettingsWidget();
    setupTestWidget();
    setupResultWidget();

    m_stackedLayout->setCurrentWidget(m_settingsWidget);
}

void TimedTestWidget::setupSettingsWidget()
{
    m_settingsWidget = new QWidget(this);

    QStringList existingCategories = CategoryColorSelector::instance().existingCategories();

    auto categoriesComboBox = new QComboBox;
    categoriesComboBox->addItems(existingCategories);

    auto categorySelectLabel = new QLabel("Choose testing category:");
    categorySelectLabel->setObjectName("categorySelectLabel");
    categorySelectLabel->setAlignment(Qt::AlignCenter);

    auto startButton = new QPushButton("Start");
    startButton->setObjectName("startButton");

    auto settingsLayout = new QVBoxLayout;
    settingsLayout->addWidget(new QWidget, 10);
    settingsLayout->addWidget(categorySelectLabel);
    settingsLayout->addWidget(categoriesComboBox);
    settingsLayout->addWidget(new QWidget, 10);
    settingsLayout->addWidget(startButton);
    settingsLayout->addWidget(new QWidget, 10);

    connect(startButton, &QPushButton::clicked, this, [this, categoriesComboBox]
    {
        emit testDataRequested(categoriesComboBox->currentText());
    });

    m_settingsWidget->setLayout(settingsLayout);

    m_stackedLayout->addWidget(m_settingsWidget);
}

void TimedTestWidget::setupTestWidget()
{
    m_testWidget = new QWidget(this);

    auto timerLabel = new QLabel(QString::number(m_remainingSeconds));
    timerLabel->setObjectName("timerLabel");
    timerLabel->setAlignment(Qt::AlignHCenter);

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->setSingleShot(false);

    connect(m_timer, &QTimer::timeout, timerLabel, [this, timerLabel]
    {
        m_remainingSeconds--;
        timerLabel->setText(QString::number(m_remainingSeconds));

        if (m_remainingSeconds == 0)
        {
            stopTest();
        }
    });

    m_answerLabel = new QLabel;
    m_answerLabel->setObjectName("answerLabel");
    m_answerLabel->setAlignment(Qt::AlignCenter);

    auto stopTestButton = new QPushButton("Stop test");
    stopTestButton->setObjectName("stopTestButton");
    connect(stopTestButton, &QPushButton::clicked, this, &TimedTestWidget::stopTest);

    auto testLayout = new QVBoxLayout;
    testLayout->addWidget(timerLabel, 1);
    testLayout->addWidget(new QWidget, 10);
    testLayout->addWidget(m_answerLabel);
    for (int i = 0; i < answerButtonsNumber; i++)
    {
        auto answerButton = new QPushButton;
        answerButton->setObjectName("answerButton");
        testLayout->addWidget(answerButton, 1);
        connect(answerButton, &QPushButton::clicked, this, [this]
        {
            auto pressedButton = static_cast<QPushButton*>(sender());
            checkAnswer(pressedButton);
            prepareTestStep();
        });
        m_answerButtons.append(answerButton);
    }
    testLayout->addWidget(new QWidget, 10);
    testLayout->addWidget(stopTestButton);

    m_testWidget->setLayout(testLayout);

    m_stackedLayout->addWidget(m_testWidget);
}

void TimedTestWidget::setupResultWidget()
{
    m_resultWidget = new QWidget(this);

    auto resultLayout = new QVBoxLayout;

    auto label = new QLabel("Results");
    label->setObjectName("resultsLabel");
    label->setAlignment(Qt::AlignHCenter);

    m_wrongAnswersLabel = new QLabel;
    m_wrongAnswersLabel->setObjectName("wrongAnswersLabel");
    m_wrongAnswersLabel->setAlignment(Qt::AlignCenter);

    auto finishTestButton = new QPushButton("Finish test");
    finishTestButton->setObjectName("finishTestButton");
    connect(finishTestButton, &QPushButton::clicked, this, [this]
    {
        m_stackedLayout->setCurrentWidget(m_settingsWidget);
    });

    resultLayout->addWidget(label, 1);
    resultLayout->addWidget(m_wrongAnswersLabel, 5);
    resultLayout->addWidget(finishTestButton, 1);

    m_resultWidget->setLayout(resultLayout);

    m_stackedLayout->addWidget(m_resultWidget);
}

void TimedTestWidget::startTest()
{
    m_wrongAnswersMap.clear();
    m_correctAnswer = nullptr;

    prepareTestStep();
    m_stackedLayout->setCurrentWidget(m_testWidget);
    m_timer->start();
}

void TimedTestWidget::stopTest()
{
    m_remainingSeconds = 60;

    m_stackedLayout->setCurrentWidget(m_resultWidget);
    clearAnswerButtons();
    m_timer->stop();

    if (m_wrongAnswersMap.size() == 0)
    {
        m_wrongAnswersLabel->setText("Congrats!\nYou successfully passed the test!");
        return;
    }

    QStringList wrongSelectedAnswers = m_wrongAnswersMap.keys();

    QString result;

    for (const auto& wrongSelectedAnswer : wrongSelectedAnswers)
    {
        auto wordPair = m_wrongAnswersMap[wrongSelectedAnswer];

        QString correctAnswerText = QStringLiteral("<font color=\"green\">%1 (correct)</font>").arg(wordPair->russianWord());
        QString wrongAnswerText = QStringLiteral("<font color=\"darkred\">%1 (your answer)</font>").arg(wrongSelectedAnswer);

        result.append(QStringLiteral("%1: %2, %3<br>")
                      .arg(wordPair->englishWord()).arg(correctAnswerText).arg(wrongAnswerText));
    }

    m_wrongAnswersLabel->setText(result);
}

void TimedTestWidget::checkAnswer(QPushButton* button)
{
    auto wordPair = m_buttonWordPairMap[button];

    if (wordPair == m_correctAnswer)
    {
        double learningQuality = wordPair->learningQuality();
        learningQuality = (learningQuality < 100) ? learningQuality + 1 : 100;
        wordPair->setLearningQuality(learningQuality);
    }
    else
    {
        m_wrongAnswersMap.insert(button->text(), m_correctAnswer);
    }

    wordPair->setLastLearningTime(QDateTime::currentDateTime());
}

void TimedTestWidget::prepareTestStep()
{
    if (m_testWordPairs.size() < 2)
    {
        stopTest();
    }

    clearAnswerButtons();
    m_buttonWordPairMap.clear();
    m_correctAnswer = nullptr;

    QList<WordPair*> selectedWordPairs;

    QList<WordPair*> testWordPairsCopy = m_testWordPairs;

    for (auto answerButton : m_answerButtons)
    {
        if (testWordPairsCopy.size() == 0)
        {
            answerButton->setDisabled(true);
            continue;
        }

        int randomWordPair = QRandomGenerator::global()->bounded(testWordPairsCopy.size());
        auto wordPair = testWordPairsCopy[randomWordPair];

        selectedWordPairs.append(wordPair);
        m_buttonWordPairMap.insert(answerButton, wordPair);

        answerButton->setText(wordPair->russianWord());

        testWordPairsCopy.removeOne(wordPair);
    }

    int randomWordPair = QRandomGenerator::global()->bounded(selectedWordPairs.size());
    auto testWordPair = selectedWordPairs[randomWordPair];

    m_answerLabel->setText(testWordPair->englishWord());
    m_correctAnswer = testWordPair;

    m_testWordPairs.removeOne(testWordPair);
}

void TimedTestWidget::clearAnswerButtons()
{
    for (auto answerButton : m_answerButtons)
    {
        answerButton->setText("");
        answerButton->setEnabled(true);
    }
}

void TimedTestWidget::setTestData(const QList<WordPair*>& wordPairs)
{
    m_testWordPairs = wordPairs;

    if (m_testWordPairs.size() < 4)
    {
        QMessageBox box;
        box.setText("Too little data to start the test.\n"
                    "Please choose another category.");
        box.exec();
        return;
    }
    startTest();
}
