#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE
class Node: public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget);

    void addEdge(Edge *edge);
    QList<Edge *> edges();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    //enum { Type = UserType + 1 };
    // int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};

#endif // NODE_H
