#include "createproductdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

CreateProductDialog::CreateProductDialog(QWidget* parent) : QDialog(parent)
{
    setMinimumSize(300, 200);

    auto layout = new QVBoxLayout(this);

    m_categoryLineEdit = new QLineEdit;
    m_categoryLineEdit->setPlaceholderText("Enter product category");
    connect(m_categoryLineEdit, &QLineEdit::textChanged, this, &CreateProductDialog::checkIfCreateEnabled);

    m_nameLineEdit = new QLineEdit;
    m_nameLineEdit->setPlaceholderText("Enter product name");
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &CreateProductDialog::checkIfCreateEnabled);

    m_priceLineEdit = new QLineEdit;
    m_priceLineEdit->setPlaceholderText("Enter price");
    connect(m_priceLineEdit, &QLineEdit::textChanged, this, &CreateProductDialog::checkIfCreateEnabled);

    m_calendarWidget = new QCalendarWidget(this);
    m_calendarWidget->setStyleSheet("QTableView { selection-background-color: yellow; selection-color: black; }");

    m_acceptButton = new QPushButton("Create");

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, this);
    buttonBox->addButton(m_acceptButton, QDialogButtonBox::AcceptRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateProductDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CreateProductDialog::reject);

    layout->addWidget(m_categoryLineEdit);
    layout->addWidget(m_nameLineEdit);
    layout->addWidget(m_priceLineEdit);
    layout->addWidget(m_calendarWidget);
    layout->addWidget(buttonBox);
}

void CreateProductDialog::checkIfCreateEnabled()
{
    bool categoryEmpty = m_categoryLineEdit->text().isEmpty();
    bool nameEmpty = m_nameLineEdit->text().isEmpty();
    bool priceEmpty = m_priceLineEdit->text().isEmpty();

    m_acceptButton->setEnabled(not categoryEmpty and not nameEmpty and not priceEmpty);
}

Product* CreateProductDialog::createProduct()
{
    return new Product(m_categoryLineEdit->text(), m_nameLineEdit->text(),
                       m_priceLineEdit->text().toDouble(), m_calendarWidget->selectedDate());
}
