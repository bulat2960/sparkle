#include "createwordpairdialog.h"

#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "../Utility/categorycolorselector.h"

CreateWordPairDialog::CreateWordPairDialog(QWidget* parent) : QDialog(parent)
{
    setMinimumWidth(300);

    auto mainLayout = new QVBoxLayout(this);


    m_englishLineEdit = new QLineEdit(this);
    m_englishLineEdit->setPlaceholderText("Type english word");

    m_russianLineEdit = new QLineEdit(this);
    m_russianLineEdit->setPlaceholderText("Type russian word");

    auto inputGridLayout = new QGridLayout;
    inputGridLayout->addWidget(new QLabel("English:", this), 0, 0);
    inputGridLayout->addWidget(m_englishLineEdit, 0, 1);
    inputGridLayout->addWidget(new QLabel("Russian:", this), 1, 0);
    inputGridLayout->addWidget(m_russianLineEdit, 1, 1);


    auto existingCategoriesGroupBox = new QGroupBox("Choose categories", this);

    QStringList existingCategories = CategoryColorSelector::instance().existingCategories();

    auto categoriesGridLayout = new QGridLayout;
    existingCategoriesGroupBox->setLayout(categoriesGridLayout);

    for (int i = 0; i < existingCategories.size(); i++)
    {
        QString category = existingCategories[i];

        auto checkBox = new QCheckBox(category, this);
        m_categoryCheckBoxes.append(checkBox);
        categoriesGridLayout->addWidget(checkBox, i / 3, i % 3);
    }


    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateWordPairDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CreateWordPairDialog::reject);


    mainLayout->addLayout(inputGridLayout);
    mainLayout->addWidget(existingCategoriesGroupBox);
    mainLayout->addWidget(buttonBox);
}

void CreateWordPairDialog::accept()
{
    if (m_englishLineEdit->text().isEmpty() or m_russianLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning!", "Please, fill in all fields.");
        return;
    }

    QDialog::accept();
}

WordPair* CreateWordPairDialog::createWordPair()
{
    QStringList selectedCategories;

    for (auto checkBox : m_categoryCheckBoxes)
    {
        if (checkBox->isChecked())
        {
            selectedCategories << checkBox->text();
        }
    }

    return new WordPair(m_englishLineEdit->text(), m_russianLineEdit->text(), selectedCategories);
}
