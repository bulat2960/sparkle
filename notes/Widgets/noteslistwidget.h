#ifndef NOTESLISTWIDGET_H
#define NOTESLISTWIDGET_H

#include "listwidget.h"

#include "notes/note.h"

class NotesListWidget : public ListWidget
{
    Q_OBJECT

public:
    NotesListWidget(QWidget* parent = nullptr);

public slots:
    void showContextMenu(const QPoint& point) override;
    void createDisplayedWidget(Note* note);

signals:
    void noteCreated(Note* note);
    void noteRemoved(Note* note);

protected slots:
    void createObject() override;
    void removeObject() override;
};

#endif // NOTESLISTWIDGET_H
