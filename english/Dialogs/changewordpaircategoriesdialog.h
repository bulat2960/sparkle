#ifndef CHANGEWORDPAIRCATEGORIESDIALOG_H
#define CHANGEWORDPAIRCATEGORIESDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QDialogButtonBox>

#include "../wordpair.h"

class ChangeWordPairCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    ChangeWordPairCategoriesDialog(WordPair* wordPair, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    QGroupBox* m_existingCategoriesGroupBox {nullptr};
    QList<QCheckBox*> m_categoryCheckBoxes;

    QGridLayout* m_checkBoxLayout {nullptr};
    QVBoxLayout* m_mainLayout {nullptr};

    WordPair* m_wordPair {nullptr};
};

#endif // CHANGEWORDPAIRCATEGORIESDIALOG_H
