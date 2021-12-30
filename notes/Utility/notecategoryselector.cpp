#include "notecategoryselector.h"

void NoteCategorySelector::addCategory(const QString& category)
{
    if (m_existingCategories.contains(category))
    {
       return;
    }

    m_existingCategories.append(category);
}

void NoteCategorySelector::removeCategory(const QString& category)
{
    if (not m_existingCategories.contains(category))
    {
       return;
    }

    m_existingCategories.removeOne(category);
}

QStringList NoteCategorySelector::existingCategories() const
{
    return m_existingCategories;
}
