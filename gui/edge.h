#ifndef EDGE_H
#define EDGE_H

#include <QObject>
#include <QGraphicsItem>

class Node;
class Edge: public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode);
    Node *sourceNode();
    Node *destNode();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // EDGE_H
