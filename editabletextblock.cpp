#include "editabletextblock.h"

#include <QVBoxLayout>
#include <QKeyEvent>

EditableTextBlock::EditableTextBlock(const QString& text, Qt::Alignment alignment, QWidget* parent) : QWidget(parent)
{
    m_label = new QLabel(text, this);
    m_label->setAlignment(alignment);
    m_label->setWordWrap(true);
    m_label->setContentsMargins(5, 0, 5, 0);

    m_textEdit = new QTextEdit(text, this);
    m_textEdit->setAlignment(alignment);
    m_textEdit->setContentsMargins(5, 0, 5, 0);

    connect(m_textEdit, &QTextEdit::textChanged, this, [this]
    {
        emit textChanged(m_textEdit->toPlainText());
    });

    m_stackedLayout = new QStackedLayout(this);
    m_stackedLayout->setSizeConstraint(QLayout::SetMinimumSize);

    m_stackedLayout->addWidget(m_label);
    m_stackedLayout->addWidget(m_textEdit);

    m_label->installEventFilter(this);
    m_textEdit->installEventFilter(this);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void EditableTextBlock::setColor(const QString& colorName)
{
    m_label->setStyleSheet(QStringLiteral("QLabel { background-color: %1; }").arg(colorName));
    m_textEdit->setStyleSheet(QStringLiteral("QTextEdit { background-color: %1; }").arg(colorName));
}

void EditableTextBlock::setEditable(bool editable)
{
    m_editable = editable;
}

void EditableTextBlock::setText(const QString& text)
{
    m_textEdit->setText(text);
    m_label->setText(text);

    QTextCursor cursor = m_textEdit->textCursor();
    cursor.setPosition(m_textEdit->document()->characterCount() - 1);
    m_textEdit->setTextCursor(cursor);
}

QString EditableTextBlock::text() const
{
    return m_label->text();
}

bool EditableTextBlock::eventFilter(QObject* watched, QEvent* event)
{
    // Do nothing if editing disabled
    if (not m_editable)
    {
        return QWidget::eventFilter(watched, event);
    }

    if (watched == m_textEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            // Write down text when press return or escape
            bool keyReturn = keyEvent->key() == Qt::Key_Return;
            bool keyEscape = keyEvent->key() == Qt::Key_Escape;

            if (not keyReturn and not keyEscape)
            {
                return QWidget::eventFilter(watched, event);
            }

            bool noShiftModifier = not (keyEvent->modifiers() & Qt::ShiftModifier);

            setText(m_textEdit->toPlainText());

            if ((keyReturn or keyEscape) and noShiftModifier)
            {
                m_stackedLayout->setCurrentIndex(0);
                emit editingFinished();
                return true;
            }

            return QWidget::eventFilter(watched, event);
        }
        else if (event->type() == QEvent::FocusOut)
        {
            // Write down text when focused out
            setText(m_textEdit->toPlainText().trimmed());
            m_stackedLayout->setCurrentIndex(0);
            emit editingFinished();
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
            setText(m_label->text());
            m_textEdit->setFocus();
        }
    }

    return QWidget::eventFilter(watched, event);
}
