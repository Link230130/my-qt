
#ifndef CUSTOMCHECKBOXDELEGATE_H
#define CUSTOMCHECKBOXDELEGATE_H


#include <QAbstractItemDelegate>


class CustomCheckBoxDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit CustomCheckBoxDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:

};

#endif // CUSTOMCHECKBOXDELEGATE_H
