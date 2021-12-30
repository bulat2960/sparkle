#ifndef CHOOSEPERIODICITYDIALOG_H
#define CHOOSEPERIODICITYDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QGridLayout>

#include "../Utility/timespan.h"

class ChoosePeriodicityDialog : public QDialog
{
    Q_OBJECT

public:
    ChoosePeriodicityDialog(QWidget* parent = nullptr);

    TimeSpan periodicity() const;

public slots:
    void accept() override;

private slots:
    void changeCustomPeriodicityLayoutVisibility(QAbstractButton* button);
    void checkCorrectPeriodicity();

private:
    QPushButton* m_acceptButton {nullptr};
    QPushButton* m_rejectButton {nullptr};

    QGroupBox* m_periodicityGroupBox {nullptr};
    QButtonGroup* m_buttonGroup {nullptr};

    QRadioButton* m_hourButton {nullptr};
    QRadioButton* m_dayButton {nullptr};
    QRadioButton* m_weekButton {nullptr};
    QRadioButton* m_customButton {nullptr};

    QComboBox* m_minuteComboBox {nullptr};
    QComboBox* m_hourComboBox {nullptr};
    QComboBox* m_dayComboBox {nullptr};
    QComboBox* m_weekComboBox {nullptr};
    QComboBox* m_monthComboBox {nullptr};

    QWidget* m_customPeriodicityWidget {nullptr};

    QVBoxLayout* m_mainLayout {nullptr};

    TimeSpan m_periodicity;

    void setupRadioButtonsLayout();
    void setupCustomPeriodicityLayout();

    void setupComboBox(QComboBox* comboBox, int maxValue);
};

#endif // CHOOSEPERIODICITYDIALOG_H
