#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include "Widgets/noteslistwidget.h"

#include "note.h"

class NotesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotesWidget(QWidget* parent = nullptr);
    ~NotesWidget();

    void loadData();
    void saveData();

private slots:
    void addNote(Note* note);
    void removeNote(Note* note);

private:
    QList<Note*> m_notes;

    NotesListWidget* m_notesListWidget {nullptr};
};

#endif // NOTESWIDGET_H
