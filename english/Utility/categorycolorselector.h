#ifndef CATEGORYCOLORSELECTOR_H
#define CATEGORYCOLORSELECTOR_H

#include <QMap>

class CategoryColorSelector
{
public:
    static CategoryColorSelector& instance()
    {
        static CategoryColorSelector theInstance;
        return theInstance;
    }

    void addCategory(const QString& category, const QString& colorSymbol);
    void removeCategory(const QString& category);
    QString colorSymbolForCategory(const QString& category) const;
    QStringList existingCategories() const;
    QStringList unusedColors() const;

private:
    CategoryColorSelector();
    CategoryColorSelector(const CategoryColorSelector& instance) = delete;
    CategoryColorSelector& operator=(const CategoryColorSelector& instance) = delete;

    QStringList m_unusedColors;
    QMap<QString, QString> m_categoryColorSymbolMap;

};

#endif // CATEGORYCOLORSELECTOR_H
