#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>
#include <QDate>
#include <QString>

class Product : public QObject
{
    Q_OBJECT

public:
    Product(const QString& category = QString(),
            const QString& name = QString(),
            double price = 0,
            const QDate& purchaseDate = QDate(),
            QObject* parent = nullptr);

    QString category() const;
    QString name() const;

    double price() const;
    QDate purchaseDate() const;

public slots:
    void setCategory(const QString& category);
    void setName(const QString& name);

    void setPrice(double price);
    void setPurchaseDate(const QDate& purchaseDate);

private:
    QString m_category;
    QString m_name;

    double m_price;
    QDate m_purchaseDate;
};

#endif // PRODUCT_H
