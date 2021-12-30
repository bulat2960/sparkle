#include "wordpairwidgetitem.h"

WordPairWidgetItem::WordPairWidgetItem(WordPairWidget* wordPairWidget, QListWidget* parent)
    : ListWidgetItem(wordPairWidget, parent)
{
    m_wordPairWidget = wordPairWidget;
}

bool WordPairWidgetItem::operator<(const QListWidgetItem& other) const
{
    const WordPairWidgetItem* otherWordPairWidgetItem = dynamic_cast<const WordPairWidgetItem*>(&other);

    if (otherWordPairWidgetItem == nullptr)
    {
        return QListWidgetItem::operator<(other);
    }

    if (m_sortingOrderString.contains("Categories number"))
    {
        int currentCategoriesCount = m_wordPairWidget->wordPair()->categories().size();
        int otherCategoriesCount = otherWordPairWidgetItem->m_wordPairWidget->wordPair()->categories().size();
        return currentCategoriesCount < otherCategoriesCount;
    }
    else if (m_sortingOrderString.contains("English words"))
    {
        QString currentEnglishWord = m_wordPairWidget->wordPair()->englishWord();
        QString otherEnglishWord = otherWordPairWidgetItem->m_wordPairWidget->wordPair()->englishWord();
        return currentEnglishWord < otherEnglishWord;
    }
    else if (m_sortingOrderString.contains("Russian words"))
    {
        QString currentRussianWord = m_wordPairWidget->wordPair()->russianWord();
        QString otherRussianWord = otherWordPairWidgetItem->m_wordPairWidget->wordPair()->russianWord();
        return currentRussianWord < otherRussianWord;
    }
    else
    {
        QStringList currentCategories = m_wordPairWidget->wordPair()->categories();
        QStringList otherCategories = otherWordPairWidgetItem->m_wordPairWidget->wordPair()->categories();

        if (currentCategories.contains(m_sortingOrderString) and not otherCategories.contains(m_sortingOrderString))
        {
            return true;
        }

        return false;
    }

    return QListWidgetItem::operator<(other);
}
