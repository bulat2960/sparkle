#ifndef CREATEPRODUCTDIALOG_H
#define CREATEPRODUCTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCalendarWidget>

#include "../product.h"

class CreateProductDialog : public QDialog
{
    Q_OBJECT

public:
    CreateProductDialog(QWidget* parent = nullptr);

    Product* createProduct();

private slots:
    void checkIfCreateEnabled();

private:
    QPushButton* m_acceptButton {nullptr};

    QLineEdit* m_categoryLineEdit {nullptr};
    QLineEdit* m_nameLineEdit {nullptr};
    QLineEdit* m_priceLineEdit {nullptr};

    QCalendarWidget* m_calendarWidget {nullptr};
};

#endif // CREATEPRODUCTDIALOG_H
