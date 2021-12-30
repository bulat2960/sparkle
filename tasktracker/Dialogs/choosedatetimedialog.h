#ifndef CHOOSEDATETIMEDIALOG_H
#define CHOOSEDATETIMEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QListView>
#include <QPushButton>
#include <QDate>
#include <QTime>

class ChooseDateTimeDialog : public QDialog
{
    Q_OBJECT

public:
    ChooseDateTimeDialog(QWidget* parent = nullptr);

    void showClearDateTimeButton();

    QDateTime getDateTime() const;

public slots:
    void accept() override;
    void clearDateTime();

private slots:
    void fillTimeList();

private:
    QCalendarWidget* m_calendarWidget {nullptr};
    QListView* m_timeList {nullptr};
    QVBoxLayout* m_mainLayout {nullptr};

    QPushButton* m_clearDateTimeButton {nullptr};

    QDate m_date;
    QTime m_time;

};

#endif // CHOOSEDATETIMEDIALOG_H
