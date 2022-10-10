#ifndef GRAPWIDGET_H
#define GRAPHWIDGET

#pragma once

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    ~GraphWidget();

    void itemMoved();

public slots:
    //拖拽
    void shuffle();
    //放大
    void zoomIn();
    //缩小
    void zoomOut();


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    
    void scaleView(qreal scaleFactor);

private:
    void iniUI();

    int                 timerId;
    Node                *centerNode;
    QGraphicsScene      *m_scene;
};
#endif // !GRAPWIDGET_H