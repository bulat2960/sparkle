#ifndef WORDPAIRWIDGETITEM_H
#define WORDPAIRWIDGETITEM_H

#include "listwidgetitem.h"

#include "wordpairwidget.h"

class WordPairWidgetItem : public ListWidgetItem
{
    Q_OBJECT

public:
    WordPairWidgetItem(WordPairWidget* wordPairWidget, QListWidget* parent = nullptr);

    bool operator<(const QListWidgetItem& other) const override;

private:
    WordPairWidget* m_wordPairWidget {nullptr};
};

#endif // WORDPAIRWIDGETITEM_H
