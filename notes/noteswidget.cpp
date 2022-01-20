#include "noteswidget.h"

#include <QApplication>
#include <QFile>
#include <QVBoxLayout>

#include "Utility/notecategoryselector.h"

NotesWidget::NotesWidget(QWidget* parent) : QWidget(parent)
{
    loadData();

    m_notesListWidget = new NotesListWidget(this);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_notesListWidget);

    connect(m_notesListWidget, &NotesListWidget::noteCreated, this, &NotesWidget::addNote);
    connect(m_notesListWidget, &NotesListWidget::noteRemoved, this, &NotesWidget::removeNote);

    for (auto note : m_notes)
    {
        m_notesListWidget->createDisplayedWidget(note);
    }
}

void NotesWidget::addNote(Note* note)
{
    m_notes.append(note);

    for (const auto& category : note->categories())
    {
        NoteCategorySelector::instance().addCategory(category);
    }
}

void NotesWidget::removeNote(Note* note)
{
    m_notes.removeOne(note);
    note->deleteLater();
}

void NotesWidget::loadData()
{
    QFile file(QApplication::applicationDirPath() + "/data/notes.txt");

    if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to load notes";
        return;
    }

    QTextStream fileStream(&file);

    QDateTime lastUpdateDateTime;
    QStringList categories;
    QString note;

    int stringToRead = 1;

    while (not fileStream.atEnd())
    {
        QString line = fileStream.readLine();

        if (stringToRead == 1)
        {
            lastUpdateDateTime = QDateTime::fromString(line, QStringLiteral("dd-MM-yyyy hh:mm:ss"));
            stringToRead = 2;
            continue;
        }
        else if (stringToRead == 2)
        {
            if (not line.isEmpty())
            {
                categories = line.split(" : ");
            }
            stringToRead = 3;
            continue;
        }
        else if (stringToRead == 3)
        {
            if (line != "-----")
            {
                if (not note.isEmpty())
                {
                    note.append("\n");
                }

                note.append(line);
            }
            else
            {
                stringToRead = 1;

                addNote(new Note(note, categories, lastUpdateDateTime));

                lastUpdateDateTime = QDateTime();
                categories.clear();
                note.clear();
            }
        }
    }

    file.close();
}

void NotesWidget::saveData()
{
    QFile file(QApplication::applicationDirPath() + "/data/notes.txt");

    if (not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file to save notes";
        return;
    }

    QTextStream fileStream(&file);

    for (auto note : m_notes)
    {
        fileStream << note->lastUpdateDateTime().toString("dd-MM-yyyy hh:mm:ss") << "\n";
        fileStream << note->categories().join(" : ") << "\n";
        fileStream << note->note().trimmed() << "\n";
        fileStream << "-----" << "\n";
    }

    file.close();
}

NotesWidget::~NotesWidget()
{
    saveData();
}
