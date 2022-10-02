#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H

#pragma once

#include <QGraphicsView>
#include <QObject>

class QWGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    QWGraphicsView(QWidget *parent = 0);
    ~QWGraphicsView();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
};
#endif // QWGRAPHICSVIEW_H