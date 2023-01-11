#include "Widget.h"
#include <QPainter>
#include <QString>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);

    initParam();

}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainterPath path(points[0]);
    path.cubicTo(points[2],points[3],points[1]);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //绘制背景
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    painter.drawRect(rect());
    painter.restore();

    //绘制鼠标实时位置
    painter.save();
    painter.setPen(QPen(Qt::red,2));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(QPointF(10,rect().height()-50),mousePosText);
    painter.restore();

    painter.setPen(QPen(Qt::black, 2));

    // 绘制 path
    painter.drawPath(path);

    // 绘制曲线上的点
    painter.setBrush(Qt::blue);
    for (int i = 0; i < points.size(); ++i) {
        painter.drawEllipse(points[i], 10, 10);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePressIndex >= 0 && mousePressIndex < 4)
    {
        points[mousePressIndex] = event->pos();
        update();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "mousePressEvent";
    mousePressPos = event->pos();
    bool ret = checkMousePress(mousePressPos);
    if(ret)
    {
        points[mousePressIndex] = mousePressPos;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "mouseReleaseEvent";
    if(mousePressIndex >= 0)
    {
        points[mousePressIndex] = event->pos();
        mousePressIndex = -1;
    }
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void Widget::initParam()
{
    startP = QPointF(70,150);
    endP = QPointF(500,350);
    cP1 = QPointF(350,150);
    cP2 = QPointF(250,300);
    points << startP << endP << cP1 << cP2;
}

bool Widget::checkMousePress(const QPoint &p)
{
    for (int i = 0; i < points.size(); ++i) {
        //距离小于10代表点中,记录下点击的点
        if(distance(mousePressPos,points.at(i)) < 10.0)
        {
            mousePressIndex = i;
            return true;
        }
    }
    mousePressIndex = -1;
    return false;
}

double Widget::distance(const QPointF p1, const QPointF p2)
{
    double xx = p1.x() - p2.x();
    double yy = p1.y() - p2.y();

    return sqrt(qPow(xx,2) + qPow(yy,2));
}
