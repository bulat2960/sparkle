#include "englishwidget.h"

#include <QPushButton>
#include <QApplication>
#include <QFile>

#include "Utility/categorycolorselector.h"

EnglishWidget::EnglishWidget(QWidget* parent) : QTabWidget(parent)
{
    loadData();

    m_dictionaryWidget = new DictionaryWidget(this);
    addTab(m_dictionaryWidget, "Dictionary");

    m_timedTestWidget = new TimedTestWidget(this);
    addTab(m_timedTestWidget, "Timed test");
    connect(m_timedTestWidget, &TimedTestWidget::testDataRequested, this, &EnglishWidget::prepareTestData);

    m_analyticsWidget = new EnglishAnalyticsWidget(this);
    addTab(m_analyticsWidget, "Analytics");

    tabBar()->setDocumentMode(true);

    connect(this, &EnglishWidget::currentChanged, this, &EnglishWidget::updateAnalytics);

    connect(m_dictionaryWidget, &DictionaryWidget::wordPairCreated, this, &EnglishWidget::addWordPair);
    connect(m_dictionaryWidget, &DictionaryWidget::wordPairRemoved, this, &EnglishWidget::removeWordPair);

    for (auto wordPair : m_wordPairs)
    {
        m_dictionaryWidget->createDisplayedWidget(wordPair);
    }
}

void EnglishWidget::updateAnalytics()
{
    QMap<QString, double> categoryData;
    categoryData["No category"] = 0;

    QMap<double, double> learningQualityData;

    for (const auto& wordPair : m_wordPairs)
    {
        QStringList categories = wordPair->categories();

        if (categories.isEmpty())
        {
            categoryData["No category"]++;
        }

        for (const auto& category : categories)
        {
            categoryData[category]++;
        }

        double learningQuality = wordPair->learningQuality();
        learningQualityData[learningQuality]++;
    }

    m_analyticsWidget->setCategoriesData(categoryData);
    m_analyticsWidget->setLearningQualityData(learningQualityData);
}

void EnglishWidget::prepareTestData(const QString& category)
{
    QList<WordPair*> wordPairs;

    for (auto wordPair : m_wordPairs)
    {
        if (wordPair->hasCategory(category))
        {
            wordPairs.append(wordPair);
        }
    }
    m_timedTestWidget->setTestData(wordPairs);
}

void EnglishWidget::addWordPair(WordPair* wordPair)
{
    m_wordPairs.append(wordPair);
}

void EnglishWidget::removeWordPair(WordPair* wordPair)
{
    m_wordPairs.removeOne(wordPair);
    wordPair->deleteLater();
}

void EnglishWidget::loadData()
{
    QFile file(QApplication::applicationDirPath() + "/data/english.txt");

    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to load words";
        return;
    }

    QTextStream fileStream(&file);

    bool categoriesLoaded = false;

    while (not fileStream.atEnd())
    {
        QString line = fileStream.readLine();

        if (line.isEmpty())
        {
            categoriesLoaded = true;
            continue;
        }

        if (not categoriesLoaded)
        {
            QStringList data = line.split("-");

            QString category = data[0];
            QString colorSymbol = data[1];

            CategoryColorSelector::instance().addCategory(category, colorSymbol);
        }
        else
        {
            QStringList data = line.split(" : ");

            QString englishWord = data[0];
            QString russianWord = data[1];

            QStringList categories;

            if (not data[2].isEmpty())
            {
                categories = data[2].split(";");
            }

            double learningQuality = data[3].toDouble();
            QDateTime lastLearningTime = QDateTime::fromString(data[4], QStringLiteral("dd-MM-yyyy hh:mm"));

            if (lastLearningTime.isValid())
            {
                while (lastLearningTime.date().day() < QDate::currentDate().day())
                {
                    lastLearningTime = lastLearningTime.addDays(1);
                    learningQuality = (learningQuality > 0) ? learningQuality - 1 : 0;
                }
            }

            lastLearningTime = QDateTime::currentDateTime();

            addWordPair(new WordPair(englishWord, russianWord, categories, learningQuality, lastLearningTime));
        }
    }

    file.close();
}

void EnglishWidget::saveData()
{
    QFile file(QApplication::applicationDirPath() + "/data/english.txt");

    if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to save words";
        return;
    }

    QTextStream fileStream(&file);

    QStringList existingCategories = CategoryColorSelector::instance().existingCategories();

    if (existingCategories.size() > 0)
    {
        for (const auto& category : existingCategories)
        {
            fileStream << category << "-" << CategoryColorSelector::instance().colorSymbolForCategory(category) << "\n";
        }
        fileStream << "\n";
    }

    for (WordPair* wordPair : m_wordPairs)
    {
        fileStream << wordPair->englishWord() << " : " << wordPair->russianWord() << " : " <<
                      wordPair->categories().join(";") << " : " << QString::number(wordPair->learningQuality()) << " : " <<
                      wordPair->lastLearningTime().toString("dd-MM-yyyy hh:mm") << "\n";
    }

    file.close();
}

EnglishWidget::~EnglishWidget()
{
    saveData();
}
