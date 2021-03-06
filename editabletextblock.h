#ifndef EDITABLETEXTBLOCK_H
#define EDITABLETEXTBLOCK_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QStackedLayout>

#include <QTextEdit>

class EditableTextBlock : public QWidget
{
    Q_OBJECT

public:
    EditableTextBlock(const QString& text = QString(), Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter, QWidget* parent = nullptr);

    bool eventFilter(QObject* watched, QEvent* event) override;

    void setEditable(bool editable);

    QString text() const;

public slots:
    void setText(const QString& text);
    void setColor(const QString& colorName);

signals:
    void textChanged(const QString& text);
    void editingFinished();

private:
    QLabel* m_label {nullptr};
    QTextEdit* m_textEdit {nullptr};

    QStackedLayout* m_stackedLayout {nullptr};

    bool m_editable {true};
};

#endif // EDITABLETEXTBLOCK_H
