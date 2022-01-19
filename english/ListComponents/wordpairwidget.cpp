#include "wordpairwidget.h"

#include <QHBoxLayout>
#include <QPushButton>

#include "../Utility/categorycolorselector.h"
#include "../Dialogs/changewordpaircategoriesdialog.h"

static const int textSize = 30;
static const int wordLabelsHeight = 50;
static const int categoryLabelsHeight = 25;

WordPairWidget::WordPairWidget(WordPair* wordPair, QWidget* parent)
    : QWidget(parent),
     m_wordPair(wordPair)
{
    m_englishEditableLabel = new EditableLabel(wordPair->englishWord(), Qt::AlignCenter);
    setupEditableLabel(m_englishEditableLabel, "orange");

    m_russianEditableLabel = new EditableLabel(wordPair->russianWord(), Qt::AlignCenter);
    setupEditableLabel(m_russianEditableLabel, "lightblue");


    auto bookButton = new QPushButton;
    bookButton->setIcon(QIcon(":/icons/book.png"));
    bookButton->setObjectName("bookButton");
    bookButton->setIconSize(QSize(wordLabelsHeight, wordLabelsHeight));

    m_learningQualityLabel = new QLabel(QStringLiteral("%1%").arg(wordPair->learningQuality()));
    m_learningQualityLabel->setAlignment(Qt::AlignCenter);
    m_learningQualityLabel->setObjectName("learningQualityLabel");
    m_learningQualityLabel->setFixedHeight(categoryLabelsHeight);
    connect(wordPair, &WordPair::learningQualityChanged, m_learningQualityLabel, [this](double learningQuality)
    {
         m_learningQualityLabel->setText(QStringLiteral("%1%").arg(learningQuality));
    });

    auto learningQualityLayout = new QVBoxLayout;
    learningQualityLayout->setSpacing(0);
    learningQualityLayout->addWidget(bookButton, 3);
    learningQualityLayout->addWidget(m_learningQualityLabel, 1);

    auto editableLabelsLayout = new QHBoxLayout;
    editableLabelsLayout->addWidget(m_englishEditableLabel);
    editableLabelsLayout->addWidget(m_russianEditableLabel);


    auto addCategoryButton = new QPushButton;
    addCategoryButton->setIcon(QIcon(":/icons/add.png"));
    addCategoryButton->setObjectName("addCategoryButton");
    connect(addCategoryButton, &QPushButton::released, this, &WordPairWidget::openAddCategoryDialog);

    m_categoryLabelsLayout = new QHBoxLayout;
    m_categoryLabelsLayout->setSpacing(10);
    m_categoryLabelsLayout->addWidget(addCategoryButton);

    auto spacerWidget = new QWidget(this);
    spacerWidget->setMinimumHeight(categoryLabelsHeight);
    m_categoryLabelsLayout->addWidget(spacerWidget, 100);

    for (const auto& category : wordPair->categories())
    {
        addCategoryLabel(category);
    }

    auto visualDataLayout = new QVBoxLayout;
    visualDataLayout->addLayout(editableLabelsLayout);
    visualDataLayout->addLayout(m_categoryLabelsLayout);

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(5);
    m_mainLayout->addLayout(visualDataLayout);
    m_mainLayout->addLayout(learningQualityLayout);

    connect(m_englishEditableLabel, &EditableLabel::textChanged, wordPair, &WordPair::setEnglishWord);
    connect(m_russianEditableLabel, &EditableLabel::textChanged, wordPair, &WordPair::setRussianWord);
    connect(wordPair, &WordPair::categoryAdded, this, &WordPairWidget::addCategoryLabel);
    connect(wordPair, &WordPair::categoryRemoved, this, &WordPairWidget::removeCategoryLabel);
}

void WordPairWidget::setupEditableLabel(EditableLabel* label, const QString& colorString)
{
    //label->setFontSize(textSize);
    label->setColor(colorString);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    label->setFixedHeight(wordLabelsHeight);
}

void WordPairWidget::openAddCategoryDialog()
{
    ChangeWordPairCategoriesDialog dialog(m_wordPair, this);
    dialog.exec();
}

WordPair* WordPairWidget::wordPair() const
{
    return m_wordPair;
}

void WordPairWidget::removeCategoryLabel(const QString &category)
{
    auto label = m_categoryLabelsMap[category];
    m_categoryLabelsLayout->removeWidget(label);
    m_categoryLabelsMap.remove(category);
    label->deleteLater();
}

void WordPairWidget::addCategoryLabel(const QString& category)
{
    QString colorSymbol = CategoryColorSelector::instance().colorSymbolForCategory(category);
    auto label = new QLabel(colorSymbol + category, this);
    label->setMinimumHeight(categoryLabelsHeight);
    label->setStyleSheet("QLabel { font-size: 18px; }");
    m_categoryLabelsLayout->insertWidget(m_categoryLabelsLayout->count() - 2, label);
    m_categoryLabelsMap.insert(category, label);
}
