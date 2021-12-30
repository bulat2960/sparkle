#ifndef NOTECATEGORYSELECTOR_H
#define NOTECATEGORYSELECTOR_H

#include <QString>
#include <QStringList>

class NoteCategorySelector
{
public:
    static NoteCategorySelector& instance()
    {
        static NoteCategorySelector theInstance;
        return theInstance;
    }

    void addCategory(const QString& category);
    void removeCategory(const QString& category);

    QStringList existingCategories() const;

private:
    NoteCategorySelector() {};
    NoteCategorySelector(const NoteCategorySelector& instance) = delete;
    NoteCategorySelector& operator=(const NoteCategorySelector& instance) = delete;

    QStringList m_existingCategories;
};

#endif // NOTECATEGORYSELECTOR_H
