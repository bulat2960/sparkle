#ifndef WORDPAIRWIDGET_H
#define WORDPAIRWIDGET_H

#include <QWidget>

#include "../wordpair.h"
#include "editablelabel.h"

class WordPairWidget : public QWidget
{
    Q_OBJECT

public:
    WordPairWidget(WordPair* wordPair, QWidget* parent = nullptr);

    WordPair* wordPair() const;

public slots:
    void addCategoryLabel(const QString& category);
    void removeCategoryLabel(const QString& category);

private slots:
    void openAddCategoryDialog();

private:
    EditableLabel* m_englishEditableLabel {nullptr};
    EditableLabel* m_russianEditableLabel {nullptr};
    QLabel* m_learningQualityLabel {nullptr};

    QMap<QString, QLabel*> m_categoryLabelsMap;
    QHBoxLayout* m_categoryLabelsLayout {nullptr};

    QHBoxLayout* m_mainLayout {nullptr};

    WordPair* m_wordPair {nullptr};

    void setupEditableLabel(EditableLabel* label, const QString& colorString);
};

#endif // WORDPAIRWIDGET_H
