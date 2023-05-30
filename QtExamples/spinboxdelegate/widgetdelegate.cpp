#include "widgetdelegate.h"
#include <QPainter>
#include <QApplication>
#include <QCheckBox>
#include <QStyle>
#include <QComboBox>
#include <QDebug>
#include <QSpinBox>
#include <QMessageBox>

WidgetDelegate::WidgetDelegate(QObject *parent) : QAbstractItemDelegate(parent)
{
    qDebug() << "WidgetDelegate construct";
    m_bSelected =false;
}

WidgetDelegate::~WidgetDelegate()
{
    qDebug() << "WidgetDelegate destruct";
}

void WidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int data = index.model()->data(index,Qt::EditRole).toInt();
    int b = qMin(option.rect.width(),option.rect.height());
    //    b -= 2;
    //    //painter->drawRect(QRectF(option.rect.x()+5,option.rect.y() + 5,option.rect.width()-10,option.rect.height()-10));
    QRectF rect = option.rect;
    double x = (rect.width()-b)/2 + rect.x();
    double y = (rect.height() - b)/2 + rect.y();
    //    painter->drawRect(QRectF(x,y,b,b));
    //    if(option.state & QStyle::State_Selected){
    //        painter->fillRect(QRectF(x+2,y+2,b-4,b-4),QColor("#00ff00"));
    //    }
    QStyleOptionButton opt;
    opt.state |= QStyle::State_Enabled;
    opt.state |= (data > 0) ? QStyle::State_On:QStyle::State_Off;
    opt.rect = QRect(x,y,b-1,b-1);
    painter->setPen(QColor("#ff0000"));
    //painter->drawRect(opt.rect);
    QApplication::style()->drawControl(QStyle::CE_CheckBox,&opt,painter);
}

QSize WidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(30,30);
}

bool WidgetDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonRelease){
        //qDebug() << "index.row=" << index.row() << ",inndex.column=" << index.column();
        QMessageBox msgBox;
        msgBox.setText(QString("The cell(%1,%2) value will be modified.").arg(index.row()).arg(index.column()));
        msgBox.exec();

        emit signalChangeValue(index);
    }
    return false;
}


