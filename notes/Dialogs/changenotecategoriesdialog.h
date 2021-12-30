#ifndef CHANGENOTECATEGORIESDIALOG_H
#define CHANGENOTECATEGORIESDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>

#include "notes/note.h"

class ChangeNoteCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    ChangeNoteCategoriesDialog(Note* note, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    Note* m_note {nullptr};

    QGroupBox* m_existingCategoriesGroupBox {nullptr};
    QGridLayout* m_checkBoxLayout {nullptr};
    QList<QCheckBox*> m_categoryCheckBoxes;

    QLineEdit* m_categoryLineEdit {nullptr};
};

#endif // CHANGENOTECATEGORIESDIALOG_H
