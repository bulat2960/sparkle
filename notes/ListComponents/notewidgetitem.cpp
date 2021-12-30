#include "notewidgetitem.h"

NoteWidgetItem::NoteWidgetItem(NoteWidget* noteWidget, QListWidget* parent)
    : ListWidgetItem(noteWidget, parent)
{
    m_noteWidget = noteWidget;
}

bool NoteWidgetItem::operator<(const QListWidgetItem& other) const
{
    const NoteWidgetItem* otherNoteWidgetItem = dynamic_cast<const NoteWidgetItem*>(&other);

    if (otherNoteWidgetItem == nullptr)
    {
        return QListWidgetItem::operator<(other);
    }

    if (m_sortingOrderString.contains("Last update"))
    {
        return m_noteWidget->note()->lastUpdateDateTime() < otherNoteWidgetItem->m_noteWidget->note()->lastUpdateDateTime();
    }
    else
    {
        QStringList currentCategories = m_noteWidget->note()->categories();
        QStringList otherCategories = otherNoteWidgetItem->m_noteWidget->note()->categories();

        if (currentCategories.contains(m_sortingOrderString) and not otherCategories.contains(m_sortingOrderString))
        {
            return true;
        }

        return false;
    }

    return QListWidgetItem::operator<(other);
}
