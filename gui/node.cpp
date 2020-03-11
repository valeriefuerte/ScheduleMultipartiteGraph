#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
Node::Node(GraphWidget *graphWidget, double size, QColor color)
    :graph(graphWidget),size(size),color(color)
{
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}


QRectF Node::boundingRect() const
{
    //Прямоугольникая граница , окрушающая фигуру

    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust); //to do сделать масштабируемость
}

QPainterPath Node::shape() const
{
    //хитбокс, если не переписывать эту функцию ,то она даст boundingRect
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    // Эллипс
    painter->setPen(QPen(Qt::black, 0));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-10, -10, 20, 20);

}

QVariant  Node::itemChange(GraphicsItemChange change, const QVariant &value){

    switch (change) {
    case ItemPositionHasChanged: //если изменилась позиция , то все ребра перемещаются
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    qDebug()<<this->pos();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

