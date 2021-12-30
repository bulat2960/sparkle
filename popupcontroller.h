#ifndef POPUPCONTROLLER_H
#define POPUPCONTROLLER_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>

#include "popupwidget.h"

class PopupController : public QObject
{
    Q_OBJECT
public:
    explicit PopupController(QWidget* parent = nullptr);

public slots:
    void createPopup(const QString& header, const QString& message);

private slots:
    void movePopups(int popupNumber);

private:
    QList<PopupWidget*> m_popupsList;
    QList<PopupWidget*> m_pendingPopupsList;

    PopupWidget* initPopup(const QString& header, const QString& message);
    void checkPendingPopups();

    QWidget* m_parent {nullptr};

};

#endif // POPUPCONTROLLER_H
