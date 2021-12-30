#ifndef SPENDINGSWIDGET_H
#define SPENDINGSWIDGET_H

#include <QTabWidget>

#include "Widgets/productlistwidget.h"
#include "Widgets/spendingsanalyticswidget.h"

class SpendingsWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit SpendingsWidget(QWidget *parent = nullptr);
    ~SpendingsWidget();

    void loadData();
    void saveData();

private slots:
    void addProduct(Product* product);
    void removeProduct(Product* product);

    void updateAnalytics();

private:
    QList<Product*> m_products;

    ProductListWidget* m_productListWidget {nullptr};
    SpendingsAnalyticsWidget* m_analyticsWidget {nullptr};
};

#endif // SPENDINGSWIDGET_H
