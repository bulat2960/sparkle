#include "spendingswidget.h"

#include <QApplication>
#include <QFile>
#include <QVBoxLayout>

#include "Utility/productcategoryselector.h"

SpendingsWidget::SpendingsWidget(QWidget *parent) : QTabWidget(parent)
{
    loadData();

    m_productListWidget = new ProductListWidget;
    addTab(m_productListWidget, "Spendings");
    connect(m_productListWidget, &ProductListWidget::productCreated, this, &SpendingsWidget::addProduct);
    connect(m_productListWidget, &ProductListWidget::productRemoved, this, &SpendingsWidget::removeProduct);

    m_analyticsWidget = new SpendingsAnalyticsWidget;
    addTab(m_analyticsWidget, "Analytics");

    tabBar()->setDocumentMode(true);

    connect(this, &SpendingsWidget::currentChanged, this, &SpendingsWidget::updateAnalytics);

    for (auto product : m_products)
    {
        m_productListWidget->createDisplayedWidget(product);
    }
}

void SpendingsWidget::updateAnalytics()
{
    int currentYear = QDate::currentDate().year();
    int daysInYear = QDate::currentDate().daysInYear();

    QMap<int, double> data;

    for (int i = 0; i < daysInYear; i++)
    {
        data[i] = 0;
    }

    for (const auto& product : m_products)
    {
        QDate date = product->purchaseDate();
        double price = product->price();

        int daysDiff = QDate(currentYear - 1, 12, 31).daysTo(date);

        data[daysDiff] += price;
    }

    m_analyticsWidget->setData(data);
}

void SpendingsWidget::addProduct(Product* product)
{
    m_products.append(product);

    ProductCategorySelector::instance().addCategory(product->category());
}

void SpendingsWidget::removeProduct(Product* product)
{
    m_products.removeOne(product);
    product->deleteLater();
}

void SpendingsWidget::loadData()
{
    QFile file(QApplication::applicationDirPath() + "/spendings.txt");

    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to load spendings";
        return;
    }

    QTextStream fileStream(&file);

    while (not fileStream.atEnd())
    {
        QString line = fileStream.readLine();

        if (line.isEmpty())
        {
            continue;
        }

        QStringList data = line.split(" : ");

        QString category = data[0];
        QString name = data[1];
        double price = data[2].toDouble();
        QDate purchaseDate = QDate::fromString(data[3], QStringLiteral("dd-MM-yyyy"));

        addProduct(new Product(category, name, price, purchaseDate));
    }

    file.close();
}

void SpendingsWidget::saveData()
{
    QFile file(QApplication::applicationDirPath() + "/spendings.txt");

    if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to save spendings";
        return;
    }

    QTextStream fileStream(&file);

    for (auto product : m_products)
    {
        fileStream << product->category() << " : " << product->name() << " : " <<
                      product->price() << " : " << product->purchaseDate().toString("dd-MM-yyyy") << "\n";
    }

    file.close();
}

SpendingsWidget::~SpendingsWidget()
{
    saveData();
}
