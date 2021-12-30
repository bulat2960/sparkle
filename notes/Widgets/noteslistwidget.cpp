#include "noteslistwidget.h"

#include <QMenu>

#include "../ListComponents/notewidget.h"
#include "../ListComponents/notewidgetitem.h"
#include "../Utility/notecategoryselector.h"
#include "../Dialogs/createnotedialog.h"

NotesListWidget::NotesListWidget(QWidget* parent) : ListWidget(parent)
{
    setSpacing(5);
}

void NotesListWidget::createDisplayedWidget(Note* note)
{
    auto noteWidget = new NoteWidget(note);
    auto item = new NoteWidgetItem(noteWidget, this);
    setItemWidget(item, noteWidget);

    scrollToItem(item);

    connect(noteWidget, &NoteWidget::heightChanged, this, [item](int height)
    {
        item->setSizeHint(QSize(item->sizeHint().width(), height));
    });

    noteWidget->updateHeight();

    connect(this, &NotesListWidget::sortingOrderChangeRequested, item, &NoteWidgetItem::changeSortingOrder);
}

void NotesListWidget::showContextMenu(const QPoint& point)
{
    QPoint globalPos = mapToGlobal(point);

    QMenu menu;
    menu.addAction("Create new note", this, &NotesListWidget::createObject);

    QAction* removeAction = menu.addAction("Remove current note", this, &NotesListWidget::removeObject);
    removeAction->setEnabled(m_lastClickedItem != nullptr);

    QMenu sortingMenu("Sort by...");
    menu.addMenu(&sortingMenu);

    sortingMenu.addAction(createSortingRequestAction("Last update (asceding)"));
    sortingMenu.addAction(createSortingRequestAction("Last update (descending)", Qt::DescendingOrder));

    QMenu categorySortingMenu("Category");
    sortingMenu.addMenu(&categorySortingMenu);

    QStringList existingCategories = NoteCategorySelector::instance().existingCategories();

    for (const auto& category : existingCategories)
    {
        categorySortingMenu.addAction(createSortingRequestAction(category));
    }

    menu.exec(globalPos);
}

void NotesListWidget::createObject()
{
    CreateNoteDialog dialog(this);
    int code = dialog.exec();

    if (code != QDialog::Accepted)
    {
        return;
    }

    auto note = dialog.createNote();
    createDisplayedWidget(note);
    emit noteCreated(note);
}

void NotesListWidget::removeObject()
{
    m_lastClickedItem->deleteLater();
}
