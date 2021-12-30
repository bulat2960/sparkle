#ifndef EDITABLELABEL_H
#define EDITABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QStackedLayout>

#include <QTextEdit>

class EditableLabel : public QWidget
{
    Q_OBJECT

public:
    EditableLabel(const QString& text = QString(), Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter, QWidget* parent = nullptr);

    bool eventFilter(QObject* watched, QEvent* event);

    void setEditable(bool editable);
    void setFontSize(int size);

    QString text() const;

public slots:
    void setText(const QString& text);
    void setColor(const QString& colorName);

signals:
    void textChanged(const QString& text);

private:
    QLabel* m_label {nullptr};
    QLineEdit* m_lineEdit {nullptr};

    QStackedLayout* m_stackedLayout {nullptr};

    bool m_editable {true};

    int m_fontSize;
    QString m_colorName;

    void updateStyleSheet();
};

#endif // EDITABLELABEL_H
