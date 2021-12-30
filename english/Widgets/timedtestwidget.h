#ifndef TIMEDTESTWIDGET_H
#define TIMEDTESTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMap>

#include "../wordpair.h"

class TimedTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimedTestWidget(QWidget *parent = nullptr);

    void setTestData(const QList<WordPair*>& wordPairs);

signals:
    void testDataRequested(const QString& category);

private slots:
    void startTest();
    void stopTest();

    void prepareTestStep();
    void checkAnswer(QPushButton* button);

private:
    QTimer* m_timer {nullptr};
    int m_remainingSeconds {60};
    QLabel* m_answerLabel {nullptr};

    QStackedLayout* m_stackedLayout {nullptr};

    QList<WordPair*> m_testWordPairs;

    QMap<QString, WordPair*> m_wrongAnswersMap;
    WordPair* m_correctAnswer {nullptr};

    QLabel* m_wrongAnswersLabel {nullptr};

    QMap<QPushButton*, WordPair*> m_buttonWordPairMap;

    QWidget* m_settingsWidget {nullptr};
    QWidget* m_testWidget {nullptr};
    QWidget* m_resultWidget {nullptr};

    QList<QPushButton*> m_answerButtons;
    void setupSettingsWidget();
    void setupTestWidget();
    void setupResultWidget();

    void clearAnswerButtons();
};

#endif // TIMEDTESTWIDGET_H
