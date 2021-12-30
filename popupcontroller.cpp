#include "popupcontroller.h"

#include <QApplication>
#include <QScreen>

static const int popupWidth = 200;
static const int popupHeight = 100;

PopupController::PopupController(QWidget *parent) : QObject(parent)
{
    m_parent = parent;
}

void PopupController::createPopup(const QString& header, const QString& message)
{
    auto popup = initPopup(header, message);

    if (m_popupsList.size() < 3)
    {
        m_popupsList.append(popup);
        popup->show();
    }
    else
    {
        m_pendingPopupsList.append(popup);
    }
}

PopupWidget* PopupController::initPopup(const QString& header, const QString& message)
{
    QSize screenSize = QApplication::primaryScreen()->size();

    auto popup = new PopupWidget(header, message, m_parent);

    connect(popup, &PopupWidget::finished, this, [this, popup]
    {
        int index = m_popupsList.indexOf(popup);
        movePopups(index + 1);
        m_popupsList.removeOne(popup);
        popup->deleteLater();
        checkPendingPopups();
    });

    if (m_popupsList.size() < 3)
    {
        popup->setGeometry(screenSize.width() - popupWidth, popupHeight * m_popupsList.size(), popupWidth, popupHeight);
    }
    else
    {
        popup->setGeometry(screenSize.width() - popupWidth, popupHeight * (m_popupsList.size() - 1), popupWidth, popupHeight);
    }

   return popup;
}

void PopupController::checkPendingPopups()
{
    if (m_pendingPopupsList.size() > 0)
    {
        auto popup = m_pendingPopupsList.takeFirst();
        m_popupsList.append(popup);
        popup->show();
    }
}

void PopupController::movePopups(int popupNumber)
{
    for (int i = popupNumber; i < m_popupsList.size(); i++)
    {
        auto currentWidget = m_popupsList[i];

        if (currentWidget != nullptr)
        {
            QRect currentWidgetGeometry = currentWidget->geometry();
            QRect prevWidgetGeometry = QRect(currentWidgetGeometry.x(), currentWidgetGeometry.y() - popupHeight,
                                             popupWidth, popupHeight);
            currentWidget->startMoveAnimation(prevWidgetGeometry);
        }
    }

}
