#include "QWGraphicsView.h"
#include <QMouseEvent>

QWGraphicsView::QWGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
}

QWGraphicsView::~QWGraphicsView()
{
}

void QWGraphicsView::mouseMoveEvent(QMouseEvent * event)
{
    //QGraphicsView的坐标
    QPoint point = event->pos();
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}

void QWGraphicsView::mousePressEvent(QMouseEvent * event)
{
    //鼠标按下左键
    if (event->button() == Qt::LeftButton)
    {
        //QGraphicsView坐标
        QPoint point = event->pos();
        emit mouseClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}
