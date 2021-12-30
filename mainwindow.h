#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QList>


#include "english/englishwidget.h"
#include "tasktracker/tasktrackerwidget.h"
#include "notes/noteswidget.h"
#include "spendings/spendingswidget.h"

#include "popupcontroller.h"
#include "remindercontroller.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void save();

private:
    QVBoxLayout* m_mainLayout {nullptr};

    QHBoxLayout* m_controlLayout {nullptr};

    QComboBox* m_chooseActivityBox {nullptr};
    QLabel* m_currentTimeLabel {nullptr};
    QPushButton* m_minimizeButton {nullptr};

    QStackedLayout* m_stackedLayout {nullptr};

    EnglishWidget* m_englishWidget {nullptr};
    TaskTrackerWidget* m_taskTrackerWidget {nullptr};
    NotesWidget* m_notesWidget {nullptr};
    SpendingsWidget* m_spendingsWidget {nullptr};

    PopupController* m_popupController {nullptr};
    ReminderController* m_reminderController {nullptr};

    void setupControlLayout();
    void setupStackedLayout();

    void changeActiveWidget();
};

#endif // MAINWINDOW_H
