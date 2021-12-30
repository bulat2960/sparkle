#ifndef NOTEWIDGETITEM_H
#define NOTEWIDGETITEM_H

#include "listwidgetitem.h"

#include "notewidget.h"

class NoteWidgetItem : public ListWidgetItem
{
    Q_OBJECT

public:
    NoteWidgetItem(NoteWidget* noteWidget, QListWidget* parent = nullptr);

    bool operator<(const QListWidgetItem& other) const override;

private:
    NoteWidget* m_noteWidget {nullptr};
};

#endif // NOTEWIDGETITEM_H
