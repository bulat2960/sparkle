#ifndef ENGLISHWIDGET_H
#define ENGLISHWIDGET_H

#include <QTabWidget>

#include "Widgets/dictionarywidget.h"
#include "Widgets/timedtestwidget.h"
#include "Widgets/englishanalyticswidget.h"
#include "wordpair.h"

class EnglishWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit EnglishWidget(QWidget* parent = nullptr);
    ~EnglishWidget();

    void loadData();
    void saveData();

private slots:
    void addWordPair(WordPair* wordPair);
    void removeWordPair(WordPair* wordPair);

    void prepareTestData(const QString& category);

    void updateAnalytics();

private:
    QList<WordPair*> m_wordPairs;

    DictionaryWidget* m_dictionaryWidget {nullptr};
    TimedTestWidget* m_timedTestWidget {nullptr};
    EnglishAnalyticsWidget* m_analyticsWidget {nullptr};
};

#endif // ENGLISHWIDGET_H
