#ifndef NODE_H
#define NODE_H

#pragma once

#include <QGraphicsItem>

class GraphWidget;
class Edge;

class Node : public QGraphicsItem
{

public:
    Node(GraphWidget *graphWidget);
    ~Node();

    void addEdge(Edge *edge);
    QList<Edge*> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void caculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
    
protected:
    QVariant itemChange(GraphicsItemChange change,const QVariant &value) override;
    
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge*>        edgeList;
    QPointF             newPos;
    GraphWidget         *graph;

};
#endif // !NODE_H