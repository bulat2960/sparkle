#ifndef PRODUCTLISTWIDGET_H
#define PRODUCTLISTWIDGET_H

#include "listwidget.h"
#include "../product.h"

class ProductListWidget : public ListWidget
{
    Q_OBJECT

public:
    ProductListWidget(QWidget* parent = nullptr);

public slots:
    void showContextMenu(const QPoint& point) override;
    void createDisplayedWidget(Product* product);

signals:
    void productCreated(Product* product);
    void productRemoved(Product* product);

protected slots:
    void createObject() override;
    void removeObject() override;
};

#endif // PRODUCTLISTWIDGET_H
