#include "popupwidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QApplication>
#include <QScreen>
#include <QPushButton>

static const int popupWidth = 200;
static const int closeButtonOffset = 10;
static const int closeButtonSize = 20;
static const int popupHideSeconds = 60;

PopupWidget::PopupWidget(const QString& header, const QString& message, QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Window);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    m_showAnimation = new QPropertyAnimation(this, "popupOpacity");
    m_showAnimation->setDuration(250);
    m_showAnimation->setStartValue(0);
    m_showAnimation->setEndValue(1);

    m_hideAnimation = new QPropertyAnimation(this, "popupOpacity");
    m_hideAnimation->setDuration(500);
    m_hideAnimation->setStartValue(1);
    m_hideAnimation->setEndValue(0);

    m_moveAnimation = new QPropertyAnimation(this, "geometry");
    m_moveAnimation->setDuration(200);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(1000 * popupHideSeconds);

    connect(m_showAnimation, &QPropertyAnimation::finished, m_timer, QOverload<>::of(&QTimer::start));
    connect(m_hideAnimation, &QPropertyAnimation::finished, this, &PopupWidget::hide);
    connect(m_timer, &QTimer::timeout, this, [this]
    {
        m_hideAnimation->start();
    });

    m_headerLabel = new QLabel(header, this);
    m_headerLabel->setAlignment(Qt::AlignCenter);
    m_headerLabel->setWordWrap(true);

    m_messageLabel = new QLabel(message, this);
    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_messageLabel->setWordWrap(true);

    auto closeButton = new QPushButton(this);
    closeButton->setFixedSize(closeButtonSize, closeButtonSize);
    closeButton->setIcon(QIcon(":/icons/close_white.png"));
    closeButton->setIconSize(QSize(closeButtonSize, closeButtonSize));
    closeButton->setGeometry(popupWidth - closeButtonSize - closeButtonOffset, closeButtonOffset, closeButtonSize, closeButtonSize);
    connect(closeButton, &QPushButton::clicked, this, [this] {
        m_timer->stop();
        m_hideAnimation->start();
    });

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_headerLabel, 1);
    layout->addWidget(m_messageLabel, 2);
}

void PopupWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0, 0, 0, 180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void PopupWidget::startMoveAnimation(const QRect& newGeometry)
{
    m_moveAnimation->setStartValue(geometry());
    m_moveAnimation->setEndValue(newGeometry);
    m_moveAnimation->start();
}

void PopupWidget::show()
{
    setWindowOpacity(0);

    QWidget::show();

    m_showAnimation->start();
}

void PopupWidget::hide()
{
    if (qFuzzyIsNull(m_popupOpacity))
    {
        QWidget::hide();
    }

    emit finished();
}

void PopupWidget::setPopupOpacity(double opacity)
{
    m_popupOpacity = opacity;
    setWindowOpacity(opacity);
}

double PopupWidget::popupOpacity() const
{
    return m_popupOpacity;
}
