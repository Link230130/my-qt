#ifndef EDGE_H
#define EDGE_H

#pragma once

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{

public:
    Edge(Node *sourceNode, Node *destNode);
    ~Edge();

    Node* sourceNode() const;
    Node* destNode() const;

    void adjust();

    enum {Type = UserType + 2};
    int type() const override{return Type;}
    
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

private:
    Node        *source;
    Node        *dest;
    QPointF     sourcePoint;
    QPointF     destPoint;
    qreal       arrowSize;
};
#endif // !EDGE_H