#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>

#include "notes/note.h"
#include "editabletextblock.h"

class NoteWidget : public QWidget
{
    Q_OBJECT

public:
    NoteWidget(Note* note, QWidget* parent = nullptr);

    Note* note() const;

public slots:
    void addCategoryLabel(const QString& category);
    void removeCategoryLabel(const QString& category);
    void updateHeight();

signals:
    void heightChanged(int height);

private slots:
    void openAddCategoryDialog();


private:
    QLabel* m_noteLabel {nullptr};
    EditableTextBlock* m_noteEditableTextBlock {nullptr};
    QLabel* m_lastUpdateDateTimeLabel {nullptr};

    QMap<QString, QLabel*> m_categoryLabelsMap;

    QHBoxLayout* m_categoryLabelsLayout {nullptr};

    QVBoxLayout* m_mainLayout {nullptr};

    Note* m_note {nullptr};

    void adjustSize();
};


#endif // NOTEWIDGET_H
