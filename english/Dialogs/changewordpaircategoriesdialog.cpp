#include "changewordpaircategoriesdialog.h"

#include <QDialogButtonBox>

#include "../Utility/categorycolorselector.h"

ChangeWordPairCategoriesDialog::ChangeWordPairCategoriesDialog(WordPair* wordPair, QWidget* parent)
    : QDialog(parent)
{
    setMinimumWidth(300);

    m_wordPair = wordPair;

    m_existingCategoriesGroupBox = new QGroupBox("Choose categories", this);

    QStringList existingCategories = CategoryColorSelector::instance().existingCategories();

    m_checkBoxLayout = new QGridLayout;

    for (int i = 0; i < existingCategories.size(); i++)
    {
        QString category = existingCategories[i];

        auto checkBox = new QCheckBox(category, this);
        checkBox->setChecked(wordPair->hasCategory(category));

        m_categoryCheckBoxes.append(checkBox);
        m_checkBoxLayout->addWidget(checkBox, i / 3, i % 3);
    }

    m_existingCategoriesGroupBox->setLayout(m_checkBoxLayout);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ChangeWordPairCategoriesDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ChangeWordPairCategoriesDialog::reject);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_existingCategoriesGroupBox);
    m_mainLayout->addWidget(buttonBox);
}

void ChangeWordPairCategoriesDialog::accept()
{
    for (auto checkBox : m_categoryCheckBoxes)
    {
        if (checkBox->isChecked())
        {
            m_wordPair->addCategory(checkBox->text());
        }
        else
        {
            m_wordPair->removeCategory(checkBox->text());
        }
    }

    QDialog::accept();
}
