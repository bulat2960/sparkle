#include "dictionarywidget.h"

#include <QScrollBar>

#include "../Dialogs/updatecategorylistdialog.h"
#include "../Utility/categorycolorselector.h"
#include "../Dialogs/createwordpairdialog.h"

DictionaryWidget::DictionaryWidget(QWidget* parent) : ListWidget(parent)
{
    m_updateCategoryListDialog = new UpdateCategoryListDialog(this);

    setSpacing(5);
}

void DictionaryWidget::createDisplayedWidget(WordPair* wordPair)
{
    auto wordPairWidget = new WordPairWidget(wordPair);
    auto item = new WordPairWidgetItem(wordPairWidget, this);
    setItemWidget(item, wordPairWidget);

    scrollToItem(item);

    connect(m_updateCategoryListDialog, &UpdateCategoryListDialog::categoryRemoved, wordPair, &WordPair::removeCategory);
    connect(this, &DictionaryWidget::sortingOrderChangeRequested, item, &WordPairWidgetItem::changeSortingOrder);

    connect(wordPair, &WordPair::categoryAdded, this, &DictionaryWidget::sort);
    connect(wordPair, &WordPair::categoryRemoved, this, &DictionaryWidget::sort);
}

void DictionaryWidget::showContextMenu(const QPoint& point)
{
    QPoint globalPos = mapToGlobal(point);

    QMenu menu;
    menu.addAction("Create new word pair", this, &DictionaryWidget::createObject);

    QAction* removeAction = menu.addAction("Remove current word pair", this, &DictionaryWidget::removeObject);
    removeAction->setEnabled(m_lastClickedItem != nullptr);

    menu.addAction("Update categories", this, [this]
    {
        m_updateCategoryListDialog->exec();
    });

    QMenu sortingMenu("Sort by...");
    menu.addMenu(&sortingMenu);

    sortingMenu.addAction(createSortingRequestAction("Categories number (ascending)"));
    sortingMenu.addAction(createSortingRequestAction("Categories number (descending)", Qt::DescendingOrder));

    sortingMenu.addAction(createSortingRequestAction("English words (ascending)"));
    sortingMenu.addAction(createSortingRequestAction("English words (descending)", Qt::DescendingOrder));

    sortingMenu.addAction(createSortingRequestAction("Russian words (ascending)"));
    sortingMenu.addAction(createSortingRequestAction("Russian words (descending)", Qt::DescendingOrder));

    QMenu categorySortingMenu("Category");
    sortingMenu.addMenu(&categorySortingMenu);

    QStringList existingCategories = CategoryColorSelector::instance().existingCategories();

    for (const auto& category : existingCategories)
    {
        categorySortingMenu.addAction(createSortingRequestAction(category));
    }

    menu.exec(globalPos);
}

void DictionaryWidget::createObject()
{
    CreateWordPairDialog createWordPairDialog(this);
    int code = createWordPairDialog.exec();

    if (code != QDialog::Accepted)
    {
        return;
    }

    auto wordPair = createWordPairDialog.createWordPair();
    createDisplayedWidget(wordPair);
    emit wordPairCreated(wordPair);
}

void DictionaryWidget::removeObject()
{
    m_lastClickedItem->deleteLater();
}
