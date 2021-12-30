#include "categorycolorselector.h"

CategoryColorSelector::CategoryColorSelector()
{
    m_unusedColors << "🔴" << "​🟠" << "​🟡" << "​🟢" << "​🔵" << "​🟣" << "🟤" << "​⚫️" << "⚪";
}

void CategoryColorSelector::addCategory(const QString &category, const QString& colorSymbol)
{
    if (m_categoryColorSymbolMap.contains(category))
    {
        return;
    }

    if (not m_unusedColors.contains(colorSymbol))
    {
        return;
    }

    m_unusedColors.removeOne(colorSymbol);
    m_categoryColorSymbolMap.insert(category, colorSymbol);
}

void CategoryColorSelector::removeCategory(const QString& category)
{
    if (not m_categoryColorSymbolMap.contains(category))
    {
        return;
    }

    QString colorSymbol = m_categoryColorSymbolMap[category];
    m_unusedColors.append(colorSymbol);
    m_categoryColorSymbolMap.remove(category);
}

QString CategoryColorSelector::colorSymbolForCategory(const QString& category) const
{
    return m_categoryColorSymbolMap[category];
}

QStringList CategoryColorSelector::existingCategories() const
{
    return m_categoryColorSymbolMap.keys();
}

QStringList CategoryColorSelector::unusedColors() const
{
    return m_unusedColors;
}
