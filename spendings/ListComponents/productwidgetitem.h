#ifndef PRODUCTWIDGETITEM_H
#define PRODUCTWIDGETITEM_H

#include "listwidgetitem.h"

#include "productwidget.h"


class ProductWidgetItem : public ListWidgetItem
{
    Q_OBJECT

public:
    ProductWidgetItem(ProductWidget* productWidget, QListWidget* parent = nullptr);

    bool operator<(const QListWidgetItem& other) const override;

private:
    ProductWidget* m_productWidget {nullptr};
};

#endif // PRODUCTWIDGETITEM_H
