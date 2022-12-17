#include "roundbutton.h"
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
#include <QDebug>

RoundButton::RoundButton(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet(R"(
                        QWidget{
                        border: 1px solid gray;
                        }
                        )");
}

void RoundButton::paintEvent(QPaintEvent *event)
{
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width()/2,height()/2);

    qreal sweepLength = 89.5;

    drawMyArc(p,45,sweepLength);
    drawMyArc(p,135,sweepLength);
    drawMyArc(p,225,sweepLength);
    drawMyArc(p,315,sweepLength);
}

void RoundButton::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        qDebug() << "鼠标左键：" << event->globalX() << "," << event->globalY();
        qDebug() << event->pos();
    }
    if(event->buttons()& Qt::RightButton)
    {
        qDebug() << "鼠标右键：" << event->globalX() << "," << event->globalY();
    }

}

void RoundButton::drawMyArc(QPainter &p, qreal startAngle, qreal sweepLength)
{
    p.save();
    int w = (width() > height())?height():width();
    QRectF rect(-(w-2)/2,-(w-2)/2,w-2,w-2);
    QPainterPath path;
    path.arcTo(rect,startAngle,sweepLength);

    QPainterPath subPath;
    QRectF subRect(-w/4,-w/4,w/2,w/2);
    subPath.addEllipse(subRect);
    path -= subPath;

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::green);
    p.drawPath(path);
    p.restore();
}
