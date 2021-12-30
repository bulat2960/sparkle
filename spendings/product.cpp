#include "product.h"

Product::Product(const QString& category,
                 const QString& name,
                 double price,
                 const QDate& purchaseDate,
                 QObject* parent)
    : QObject(parent)
{
    m_category = category;
    m_name = name;
    m_price = price;
    m_purchaseDate = purchaseDate;
}

QString Product::name() const
{
    return m_name;
}

QString Product::category() const
{
    return m_category;
}

double Product::price() const
{
    return m_price;
}

QDate Product::purchaseDate() const
{
    return m_purchaseDate;
}

void Product::setName(const QString& name)
{
    m_name = name;
}

void Product::setCategory(const QString& category)
{
    m_category = category;
}

void Product::setPrice(double price)
{
    m_price = price;
}

void Product::setPurchaseDate(const QDate& purchaseDate)
{
    m_purchaseDate = purchaseDate;
}
