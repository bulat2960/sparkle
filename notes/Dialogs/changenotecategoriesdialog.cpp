#include "changenotecategoriesdialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>

#include "../Utility/notecategoryselector.h"

ChangeNoteCategoriesDialog::ChangeNoteCategoriesDialog(Note* note, QWidget* parent) : QDialog(parent)
{
    setMinimumWidth(300);

    m_note = note;

    auto layout = new QVBoxLayout(this);

    auto controlsLayout = new QHBoxLayout;

    m_categoryLineEdit = new QLineEdit(this);
    m_categoryLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto createButton = new QPushButton("Create", this);
    createButton->setEnabled(false);
    connect(m_categoryLineEdit, &QLineEdit::textChanged, createButton, [createButton](const QString& text)
    {
        createButton->setEnabled(not text.isEmpty());
    });

    controlsLayout->addWidget(m_categoryLineEdit);
    controlsLayout->addWidget(createButton);

    m_existingCategoriesGroupBox = new QGroupBox("Choose categories", this);

    QStringList existingCategories = NoteCategorySelector::instance().existingCategories();

    m_checkBoxLayout = new QGridLayout;
    connect(createButton, &QPushButton::clicked, this, [this]
    {
        QStringList categories = m_note->categories();

        QString category = m_categoryLineEdit->text();
        m_categoryLineEdit->clear();

        if (categories.contains(category))
        {
            QMessageBox::information(this, "Information", "This category already exists.");
            return;
        }

        int buttonsCount = m_checkBoxLayout->count();
        auto checkBox = new QCheckBox(category, this);
        m_checkBoxLayout->addWidget(checkBox, buttonsCount / 3, buttonsCount % 3);
        m_categoryCheckBoxes.append(checkBox);
        NoteCategorySelector::instance().addCategory(category);
    });

    for (int i = 0; i < existingCategories.size(); i++)
    {
        QString category = existingCategories[i];

        auto checkBox = new QCheckBox(category, this);
        checkBox->setChecked(note->hasCategory(category));

        m_categoryCheckBoxes.append(checkBox);
        m_checkBoxLayout->addWidget(checkBox, i / 3, i % 3);
    }

    m_existingCategoriesGroupBox->setLayout(m_checkBoxLayout);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ChangeNoteCategoriesDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ChangeNoteCategoriesDialog::reject);

    layout->addLayout(controlsLayout);
    layout->addWidget(m_existingCategoriesGroupBox);
    layout->addWidget(buttonBox);
}

void ChangeNoteCategoriesDialog::accept()
{
    for (auto checkBox : m_categoryCheckBoxes)
    {
        if (checkBox->isChecked())
        {
            m_note->addCategory(checkBox->text());
        }
        else
        {
            m_note->removeCategory(checkBox->text());
        }
    }

    QDialog::accept();
}
