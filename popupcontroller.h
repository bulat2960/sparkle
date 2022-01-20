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
    void createPopup(const QString& title, const QString& message);
    void createPopup(const QString& title, const QString& message, int lifetimeSeconds);

    void setActive(bool active);
    bool isActive() const;

private slots:
    void movePopups(int popupNumber);

private:
    QList<PopupWidget*> m_popupsList;
    QList<PopupWidget*> m_pendingPopupsList;

    PopupWidget* initPopup(const QString& title, const QString& message, int lifetimeSeconds);
    void checkPendingPopups();

    QWidget* m_parent {nullptr};

    bool m_active {true};

};

#endif // POPUPCONTROLLER_H
