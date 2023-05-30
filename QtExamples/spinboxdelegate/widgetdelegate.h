#ifndef WIDGETDELEGATE_H
#define WIDGETDELEGATE_H

#include <QAbstractItemDelegate>

class WidgetDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit WidgetDelegate(QObject *parent = nullptr);
    ~WidgetDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void signalChangeValue(const QModelIndex& index);

public slots:

private:
    bool m_bSelected;
};

#endif // WIDGETDELEGATE_H
