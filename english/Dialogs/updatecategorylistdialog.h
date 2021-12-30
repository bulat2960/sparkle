#ifndef UPDATECATEGORYLISTDIALOG_H
#define UPDATECATEGORYLISTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class UpdateCategoryListDialog : public QDialog
{
    Q_OBJECT

public:
    UpdateCategoryListDialog(QWidget* parent = nullptr);

public slots:
    int exec() override;

signals:
    void categoryRemoved(const QString& category);

private:
    QListWidget* m_listWidget {nullptr};

    QLineEdit* m_categoryLineEdit {nullptr};
    QComboBox* m_colorComboBox {nullptr};
    QComboBox* m_removeCategoryComboBox {nullptr};

    QPushButton* m_okButton {nullptr};
    QPushButton* m_addButton {nullptr};
    QPushButton* m_removeButton {nullptr};

    void addCategory();
    void removeCategory();
    void updateControls();
};

#endif // UPDATECATEGORYLISTDIALOG_H
