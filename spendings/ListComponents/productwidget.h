#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "spendings/product.h"
#include "editablelabel.h"

class ProductWidget : public QWidget
{
public:
    ProductWidget(Product* product, QWidget* parent = nullptr);
    ~ProductWidget();

    Product* product() const;

private:
    EditableLabel* m_categoryEditableLabel {nullptr};
    EditableLabel* m_nameEditableLabel {nullptr};
    EditableLabel* m_priceEditableLabel {nullptr};

    Product* m_product {nullptr};
};

#endif // PRODUCTWIDGET_H