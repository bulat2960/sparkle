#include "productlistwidget.h"

#include <QMenu>

#include "../ListComponents/productwidget.h"
#include "../ListComponents/productwidgetitem.h"
#include "../Dialogs/createproductdialog.h"

#include "../Utility/productcategoryselector.h"

ProductListWidget::ProductListWidget(QWidget* parent) : ListWidget(parent)
{

}

void ProductListWidget::createDisplayedWidget(Product* product)
{
    auto productWidget = new ProductWidget(product, this);
    auto item = new ProductWidgetItem(productWidget, this);
    setItemWidget(item, productWidget);

    scrollToItem(item);

    connect(this, &ProductListWidget::sortingOrderChangeRequested, item, &ProductWidgetItem::changeSortingOrder);

    connect(productWidget, &ProductWidget::destroyed, this, [this, product]
    {
        emit productRemoved(product);
    });
}

void ProductListWidget::showContextMenu(const QPoint& point)
{
    QPoint globalPos = mapToGlobal(point);

    QMenu menu;
    menu.addAction("Create new product", this, &ProductListWidget::createObject);

    QAction* removeAction = menu.addAction("Remove current product", this, &ProductListWidget::removeObject);
    removeAction->setEnabled(m_lastClickedItem != nullptr);

    QMenu sortingMenu("Sort by...");
    menu.addMenu(&sortingMenu);

    sortingMenu.addAction(createSortingRequestAction("Purchase date (asceding)"));
    sortingMenu.addAction(createSortingRequestAction("Purchase date (descending)", Qt::DescendingOrder));

    sortingMenu.addAction(createSortingRequestAction("Price (asceding)"));
    sortingMenu.addAction(createSortingRequestAction("Price (descending)", Qt::DescendingOrder));

    QMenu categorySortingMenu("Category");
    sortingMenu.addMenu(&categorySortingMenu);

    QStringList existingCategories = ProductCategorySelector::instance().existingCategories();

    for (const auto& category : existingCategories)
    {
        categorySortingMenu.addAction(createSortingRequestAction(category));
    }

    menu.exec(globalPos);
}

void ProductListWidget::createObject()
{
    CreateProductDialog dialog(this);
    int code = dialog.exec();

    if (code != QDialog::Accepted)
    {
        return;
    }

    auto product = dialog.createProduct();
    createDisplayedWidget(product);
    emit productCreated(product);
}

void ProductListWidget::removeObject()
{
    m_lastClickedItem->deleteLater();
}
