#include "productwidgetitem.h"

ProductWidgetItem::ProductWidgetItem(ProductWidget* productWidget, QListWidget* parent)
    : ListWidgetItem(productWidget, parent)
{
    m_productWidget = productWidget;
}

bool ProductWidgetItem::operator<(const QListWidgetItem& other) const
{
    const ProductWidgetItem* otherProductWidgetItem = dynamic_cast<const ProductWidgetItem*>(&other);

    if (otherProductWidgetItem == nullptr)
    {
        return QListWidgetItem::operator<(other);
    }

    if (m_sortingOrderString.contains("Purchase date"))
    {
        return m_productWidget->product()->purchaseDate() < otherProductWidgetItem->m_productWidget->product()->purchaseDate();
    }
    else if (m_sortingOrderString.contains("Price"))
    {
        return m_productWidget->product()->price() < otherProductWidgetItem->m_productWidget->product()->price();
    }
    else
    {
        QString currentCategory = m_productWidget->product()->category();
        QString otherCategory = otherProductWidgetItem->m_productWidget->product()->category();

        return currentCategory == m_sortingOrderString and otherCategory != m_sortingOrderString;
    }

    return QListWidgetItem::operator<(other);
}
