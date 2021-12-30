#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class PopupWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double popupOpacity READ popupOpacity WRITE setPopupOpacity)

public:
    explicit PopupWidget(const QString& header, const QString& message, QWidget* parent = nullptr);

public slots:
    void show();
    void hide();

    void startMoveAnimation(const QRect& newGeometry);

signals:
    void finished();

protected:
    void paintEvent(QPaintEvent* event);

private:
    QLabel* m_headerLabel {nullptr};
    QLabel* m_messageLabel {nullptr};

    QTimer* m_timer {nullptr};

    QPropertyAnimation* m_showAnimation {nullptr};
    QPropertyAnimation* m_hideAnimation {nullptr};
    QPropertyAnimation* m_moveAnimation {nullptr};

    double m_popupOpacity;

    void setPopupOpacity(double opacity);
    double popupOpacity() const;
};

#endif // POPUPWIDGET_H
