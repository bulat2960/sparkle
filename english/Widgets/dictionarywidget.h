#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QMap>
#include <QListWidgetItem>

#include "../wordpair.h"
#include "../ListComponents/wordpairwidget.h"
#include "../ListComponents/wordpairwidgetitem.h"
#include "../Dialogs/updatecategorylistdialog.h"
#include "listwidget.h"

class DictionaryWidget : public ListWidget
{
    Q_OBJECT

public:
    DictionaryWidget(QWidget* parent = nullptr);

public slots:
    void showContextMenu(const QPoint& point) override;
    void createDisplayedWidget(WordPair* wordPair);

signals:
    void wordPairCreated(WordPair* wordPair);
    void wordPairRemoved(WordPair* wordPair);

protected slots:
    void createObject() override;
    void removeObject() override;

private:
    UpdateCategoryListDialog* m_updateCategoryListDialog {nullptr};

};

#endif // DICTIONARYWIDGET_H
