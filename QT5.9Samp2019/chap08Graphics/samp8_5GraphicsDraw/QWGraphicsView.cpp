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

void QWGraphicsView::mouseDoubleClickEvent(QMouseEvent * event)
{
    //鼠标双击事件
    if (event->button() == Qt::LeftButton)
    {
        QPoint point = event->pos();//QGraphicsView的坐标
        emit mouseDoubleClick(point);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void QWGraphicsView::keyPressEvent(QKeyEvent * event)
{
    //按键事件
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}
