#ifndef CREATEWORDPAIRDIALOG_H
#define CREATEWORDPAIRDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>


#include "../wordpair.h"

class CreateWordPairDialog : public QDialog
{
    Q_OBJECT

public:
    CreateWordPairDialog(QWidget* parent = nullptr);

    WordPair* createWordPair();

public slots:
    void accept() override;

private:
    QLineEdit* m_englishLineEdit {nullptr};
    QLineEdit* m_russianLineEdit {nullptr};

    QList<QCheckBox*> m_categoryCheckBoxes;
};

#endif // CREATEWORDPAIRDIALOG_H
