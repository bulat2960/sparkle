#ifndef PRODUCTCATEGORYSELECTOR_H
#define PRODUCTCATEGORYSELECTOR_H

#include <QStringList>
#include <QString>

class ProductCategorySelector
{
public:
    static ProductCategorySelector& instance()
    {
        static ProductCategorySelector theInstance;
        return theInstance;
    }

    void addCategory(const QString& category);
    void removeCategory(const QString& category);

    QStringList existingCategories() const;

private:
    ProductCategorySelector() {};
    ProductCategorySelector(const ProductCategorySelector& instance) = delete;
    ProductCategorySelector& operator=(const ProductCategorySelector& instance) = delete;

    QStringList m_existingCategories;
};

#endif // PRODUCTCATEGORYSELECTOR_H
