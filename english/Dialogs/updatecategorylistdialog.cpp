#include "updatecategorylistdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QDialogButtonBox>

#include "../Utility/categorycolorselector.h"

UpdateCategoryListDialog::UpdateCategoryListDialog(QWidget* parent) : QDialog(parent)
{
    setFixedSize(350, 300);

    setWindowModality(Qt::WindowModal);

    auto mainLayout = new QVBoxLayout(this);


    m_listWidget = new QListWidget(this);
    m_listWidget->setSelectionMode(QListWidget::NoSelection);
    m_listWidget->setEditTriggers(QListWidget::NoEditTriggers);

    auto existingCategoriesLayout = new QVBoxLayout;
    existingCategoriesLayout->addWidget(m_listWidget);

    auto existingCategoriesGroup = new QGroupBox("Existing categories", this);
    existingCategoriesGroup->setLayout(existingCategoriesLayout);


    m_categoryLineEdit = new QLineEdit(this);
    m_categoryLineEdit->setPlaceholderText("New category name");

    m_colorComboBox = new QComboBox(this);
    m_colorComboBox->addItems(CategoryColorSelector::instance().unusedColors());

    m_addButton = new QPushButton("Add", this);
    connect(m_addButton, &QPushButton::clicked, this, &UpdateCategoryListDialog::addCategory);

    auto createCategoryLayout = new QHBoxLayout;
    createCategoryLayout->addWidget(m_categoryLineEdit, 3);
    createCategoryLayout->addWidget(m_colorComboBox, 1);
    createCategoryLayout->addWidget(m_addButton, 1);

    auto createCategoryGroup = new QGroupBox("Create category", this);
    createCategoryGroup->setLayout(createCategoryLayout);


    m_removeCategoryComboBox = new QComboBox(this);

    m_removeButton = new QPushButton("Remove", this);
    connect(m_removeButton, &QPushButton::clicked, this, &UpdateCategoryListDialog::removeCategory);

    auto removeCategoryLayout = new QHBoxLayout;
    removeCategoryLayout->addWidget(m_removeCategoryComboBox, 4);
    removeCategoryLayout->addWidget(m_removeButton, 1);

    auto removeCategoryGroup = new QGroupBox("Remove category", this);
    removeCategoryGroup->setLayout(removeCategoryLayout);


    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &UpdateCategoryListDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &UpdateCategoryListDialog::reject);

    mainLayout->addWidget(existingCategoriesGroup);
    mainLayout->addWidget(createCategoryGroup);
    mainLayout->addWidget(removeCategoryGroup);
    mainLayout->addWidget(buttonBox);

    updateControls();
}

void UpdateCategoryListDialog::addCategory()
{
    QString category = m_categoryLineEdit->text();
    m_categoryLineEdit->clear();

    if (category.isEmpty())
    {
        return;
    }

    QString colorSymbol = m_colorComboBox->currentText();
    CategoryColorSelector::instance().addCategory(category, colorSymbol);

    updateControls();
}

void UpdateCategoryListDialog::removeCategory()
{
    if (m_removeCategoryComboBox->count() == 0)
    {
        return;
    }

    QString category = m_removeCategoryComboBox->currentText();

    int code = QMessageBox::question(this, "Remove category",
                                     QStringLiteral("Are you sure you want to remove category '%1'?\n"
                                                    "There may be entities that use this category.").arg(category));

    if (code == QMessageBox::No)
    {
        return;
    }

    CategoryColorSelector::instance().removeCategory(category);
    updateControls();

    emit categoryRemoved(category);
}

void UpdateCategoryListDialog::updateControls()
{
    m_listWidget->clear();
    m_colorComboBox->clear();
    m_removeCategoryComboBox->clear();

    QStringList existingCategories = CategoryColorSelector::instance().existingCategories();

    for (const auto& category : existingCategories)
    {
        auto item = new QListWidgetItem(category, m_listWidget);
        item->setTextAlignment(Qt::AlignCenter);
        m_listWidget->addItem(item);
    }

    m_colorComboBox->addItems(CategoryColorSelector::instance().unusedColors());
    m_removeCategoryComboBox->addItems(CategoryColorSelector::instance().existingCategories());

    m_removeCategoryComboBox->setEnabled(m_removeCategoryComboBox->count() > 0);
    m_removeButton->setEnabled(m_removeCategoryComboBox->count() > 0);

    m_categoryLineEdit->setEnabled(m_colorComboBox->count() > 0);
    m_colorComboBox->setEnabled(m_colorComboBox->count() > 0);
    m_addButton->setEnabled(m_colorComboBox->count() > 0);
}

int UpdateCategoryListDialog::exec()
{
    updateControls();
    return QDialog::exec();
}
