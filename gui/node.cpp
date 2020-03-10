#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
Node::Node(GraphWidget *graphWidget)
{

}

void Node::addEdge(Edge *edge)
{

}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
QVariant  Node::itemChange(GraphicsItemChange change, const QVariant &value){

}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){

}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}
QRectF Node::boundingRect() const {
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}
QPainterPath Node::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

