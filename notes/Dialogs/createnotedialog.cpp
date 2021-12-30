#include "createnotedialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

CreateNoteDialog::CreateNoteDialog(QWidget* parent) : QDialog(parent)
{
    setMinimumSize(300, 200);

    auto layout = new QVBoxLayout(this);

    m_noteTextEdit = new QTextEdit;
    m_noteTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_acceptButton = new QPushButton("Create");
    connect(m_noteTextEdit, &QTextEdit::textChanged, m_acceptButton, [this]
    {
        m_acceptButton->setEnabled(not m_noteTextEdit->toPlainText().isEmpty());
    });

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, this);
    buttonBox->addButton(m_acceptButton, QDialogButtonBox::AcceptRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateNoteDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CreateNoteDialog::reject);

    auto label = new QLabel("New note text:");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    layout->addWidget(label);
    layout->addWidget(m_noteTextEdit);
    layout->addWidget(buttonBox);
}

Note* CreateNoteDialog::createNote()
{
    return new Note(m_noteTextEdit->toPlainText(), QStringList(), QDateTime::currentDateTime());
}
