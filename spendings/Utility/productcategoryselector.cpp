#include "productcategoryselector.h"

void ProductCategorySelector::addCategory(const QString& category)
{
    if (m_existingCategories.contains(category))
    {
       return;
    }

    m_existingCategories.append(category);
}

void ProductCategorySelector::removeCategory(const QString& category)
{
    if (not m_existingCategories.contains(category))
    {
       return;
    }

    m_existingCategories.removeOne(category);
}

QStringList ProductCategorySelector::existingCategories() const
{
    return m_existingCategories;
}
