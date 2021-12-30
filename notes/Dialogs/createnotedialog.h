#ifndef CREATENOTEDIALOG_H
#define CREATENOTEDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>

#include "notes/note.h"

class CreateNoteDialog : public QDialog
{
public:
    CreateNoteDialog(QWidget* parent = nullptr);

    Note* createNote();

private:
    QPushButton* m_acceptButton {nullptr};

    QTextEdit* m_noteTextEdit {nullptr};
};

#endif // CREATENOTEDIALOG_H
