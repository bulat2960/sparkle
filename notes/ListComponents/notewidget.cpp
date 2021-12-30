#include "notewidget.h"

#include <QHBoxLayout>
#include <QPushButton>

#include "../Dialogs/changenotecategoriesdialog.h"

static const int textSize = 25;
static const int categoryLabelHeight = 25;
static constexpr int textBlockMinimumHeight = textSize * 3;

NoteWidget::NoteWidget(Note* note, QWidget* parent)
    : QWidget(parent),
      m_note(note)
{
    m_noteEditableTextBlock = new EditableTextBlock(note->note(), Qt::AlignLeft | Qt::AlignTop);

    m_noteEditableTextBlock->setFontSize(textSize);
    m_noteEditableTextBlock->setColor("lightgray");
    m_noteEditableTextBlock->setMinimumHeight(textBlockMinimumHeight);

    auto addCategoryButton = new QPushButton;
    addCategoryButton->setIcon(QIcon(":/icons/add.png"));
    addCategoryButton->setStyleSheet("QPushButton { border: 0px; }");
    connect(addCategoryButton, &QPushButton::released, this, &NoteWidget::openAddCategoryDialog);

    m_lastUpdateDateTimeLabel = new QLabel(note->lastUpdateDateTime().toString("dd-MM-yyyy hh:mm:ss"));
    m_lastUpdateDateTimeLabel->setFixedHeight(categoryLabelHeight);
    m_lastUpdateDateTimeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QFont font;
    font.setPixelSize(20);
    m_lastUpdateDateTimeLabel->setFont(font);

    m_categoryLabelsLayout = new QHBoxLayout;
    m_categoryLabelsLayout->setSpacing(10);
    m_categoryLabelsLayout->addWidget(addCategoryButton);
    m_categoryLabelsLayout->addWidget(new QWidget, 100);
    m_categoryLabelsLayout->addWidget(m_lastUpdateDateTimeLabel);

    for (const auto& category : note->categories())
    {
        addCategoryLabel(category);
    }

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(5);
    m_mainLayout->addWidget(m_noteEditableTextBlock);
    m_mainLayout->addLayout(m_categoryLabelsLayout);

    connect(m_noteEditableTextBlock, &EditableTextBlock::textChanged, this, [this](const QString& text)
    {
        m_note->setNote(text);
        m_note->setLastUpdateDateTime(QDateTime::currentDateTime());
        m_lastUpdateDateTimeLabel->setText(m_note->lastUpdateDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        updateHeight();
    });

    connect(note, &Note::categoryAdded, this, &NoteWidget::addCategoryLabel);
    connect(note, &Note::categoryRemoved, this, &NoteWidget::removeCategoryLabel);
}

void NoteWidget::updateHeight()
{
    QString text = m_note->note();
    QStringList paragraphs = text.split("\n");

    int lines = paragraphs.size();

    for (const auto& paragraph : paragraphs)
    {
        if (paragraph.size() >= 110)
        {
            lines += floor(paragraph.size() / 110);
        }
    }

    int mainLayoutMargins = m_mainLayout->contentsMargins().top() + m_mainLayout->contentsMargins().bottom();
    int mainLayoutSpacing = m_mainLayout->spacing();

    int newTextBlockHeight = (lines) * (textSize + 10);

    if (newTextBlockHeight > textBlockMinimumHeight)
    {
        m_noteEditableTextBlock->setMinimumHeight(newTextBlockHeight);
    }
    else
    {
        newTextBlockHeight = textBlockMinimumHeight;
        m_noteEditableTextBlock->setMinimumHeight(textBlockMinimumHeight);
    }

    int height = newTextBlockHeight + mainLayoutSpacing + categoryLabelHeight + mainLayoutMargins + 15;

    emit heightChanged(height);
}

void NoteWidget::openAddCategoryDialog()
{
    ChangeNoteCategoriesDialog dialog(m_note, this);
    dialog.exec();
}

Note* NoteWidget::note() const
{
    return m_note;
}

void NoteWidget::removeCategoryLabel(const QString &category)
{
    auto label = m_categoryLabelsMap[category];
    m_categoryLabelsLayout->removeWidget(label);
    m_categoryLabelsMap.remove(category);
    label->deleteLater();
}

void NoteWidget::addCategoryLabel(const QString& category)
{
    auto label = new QLabel(QStringLiteral("#%1").arg(category), this);
    label->setFixedHeight(categoryLabelHeight);

    QFont font = label->font();
    font.setUnderline(true);
    font.setPixelSize(15);
    label->setFont(font);

    m_categoryLabelsLayout->insertWidget(m_categoryLabelsLayout->count() - 3, label);
    m_categoryLabelsMap.insert(category, label);
}

NoteWidget::~NoteWidget()
{
    m_note->deleteLater();
}
