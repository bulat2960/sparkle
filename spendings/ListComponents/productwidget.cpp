#include "productwidget.h"

#include <QHBoxLayout>

static const int lineHeight = 30;

ProductWidget::ProductWidget(Product* product, QWidget* parent)
    : QWidget(parent),
      m_product(product)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);

    m_categoryEditableLabel = new EditableLabel(product->category(), Qt::AlignCenter, this);
    m_categoryEditableLabel->setColor("lightgray");
    m_categoryEditableLabel->setMinimumHeight(lineHeight);

    m_nameEditableLabel = new EditableLabel(product->name(), Qt::AlignCenter, this);
    m_nameEditableLabel->setColor("darkgray");
    m_nameEditableLabel->setMinimumHeight(lineHeight);

    m_priceEditableLabel = new EditableLabel(QString::number(product->price()), Qt::AlignCenter, this);
    m_priceEditableLabel->setColor("lightgreen");
    m_priceEditableLabel->setMinimumHeight(lineHeight);

    mainLayout->addWidget(m_categoryEditableLabel);
    mainLayout->addWidget(m_nameEditableLabel);
    mainLayout->addWidget(m_priceEditableLabel);


    connect(m_categoryEditableLabel, &EditableLabel::textChanged, product, &Product::setCategory);
    connect(m_nameEditableLabel, &EditableLabel::textChanged, product, &Product::setName);
    connect(m_priceEditableLabel, &EditableLabel::textChanged, product, [product](const QString& text)
    {
        bool ok;
        double price = text.toDouble(&ok);
        product->setPrice(ok ? price : 0);
    });
}

Product* ProductWidget::product() const
{
    return m_product;
}
