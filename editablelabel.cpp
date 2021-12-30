#include "editablelabel.h"

#include <QVBoxLayout>
#include <QKeyEvent>

EditableLabel::EditableLabel(const QString& text, Qt::Alignment alignment, QWidget* parent) : QWidget(parent)
{
    m_label = new QLabel(text, this);
    m_label->setAlignment(alignment);
    m_label->setWordWrap(true);
    m_label->setContentsMargins(10, 0, 10, 0);

    m_lineEdit = new QLineEdit(text, this);
    m_lineEdit->setAlignment(alignment);

    connect(m_lineEdit, &QLineEdit::textChanged, this, &EditableLabel::textChanged);

    m_stackedLayout = new QStackedLayout(this);
    m_stackedLayout->setSizeConstraint(QLayout::SetMinimumSize);

    m_stackedLayout->addWidget(m_label);
    m_stackedLayout->addWidget(m_lineEdit);

    m_label->installEventFilter(this);
    m_lineEdit->installEventFilter(this);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void EditableLabel::updateStyleSheet()
{
    m_label->setStyleSheet(QStringLiteral("QLabel { border-radius: 10px; background-color: %1; font-size: %2px; }").arg(m_colorName).arg(m_fontSize));
    m_lineEdit->setStyleSheet(QStringLiteral("QLineEdit { border-radius: 10px; background-color: %1; font-size: %2px; }").arg(m_colorName).arg(m_fontSize));
}

void EditableLabel::setColor(const QString& colorName)
{
    m_colorName = colorName;
    updateStyleSheet();
}

void EditableLabel::setEditable(bool editable)
{
    m_editable = editable;
}

void EditableLabel::setFontSize(int size)
{
    m_fontSize = size;
    updateStyleSheet();
}

void EditableLabel::setText(const QString& text)
{
    m_lineEdit->setText(text);
    m_label->setText(text);
}

QString EditableLabel::text() const
{
    return m_label->text();
}

bool EditableLabel::eventFilter(QObject* watched, QEvent* event)
{
    // Do nothing if editing disabled
    if (not m_editable)
    {
        return QWidget::eventFilter(watched, event);
    }

    if (watched == m_lineEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            // Write down text when press return, escape or enter
            bool keyReturn = keyEvent->key() == Qt::Key_Return;
            bool keyEscape = keyEvent->key() == Qt::Key_Escape;
            bool keyEnter  = keyEvent->key() == Qt::Key_Enter;

            if (keyReturn or keyEscape or keyEnter)
            {
                m_label->setText(m_lineEdit->text());
                m_stackedLayout->setCurrentIndex(0);
            }
        }
        else if (event->type() == QEvent::FocusOut)
        {
            // Write down text when focused out
            m_label->setText(m_lineEdit->text());
            m_stackedLayout->setCurrentIndex(0);
        }

    }
    else if (watched == m_label)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        // Enable editing if doubleclicked using left button
        bool doubleClick = mouseEvent->type() == QMouseEvent::MouseButtonDblClick;
        bool leftButton = mouseEvent->button() == Qt::LeftButton;

        if (doubleClick and leftButton)
        {
            m_stackedLayout->setCurrentIndex(1);
            m_lineEdit->setText(m_label->text());
            m_lineEdit->setFocus();
        }
    }

    return QWidget::eventFilter(watched, event);
}
