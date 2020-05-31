#include "edge.h"
#include "node.h"

#include <qmath.h>
#include <QPainter>
#include <QDebug>
Edge::Edge(Node *sourceNode, Node *destNode)
{
    setAcceptedMouseButtons(nullptr);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}
void Edge::adjust() {

    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(source->getSize())) {
        QPointF edgeOffset((line.dx() * source->getSize()/2) / length, (line.dy() * source->getSize()/2) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

void Edge::changeEdgeVisibility()
{
    if ((!this->destNode()->isVisible()) || (!this->sourceNode()->isVisible())) {
        //qDebug()<<"edgeHided";
        this->hide();
    } else {
        //qDebug()<<"edgeShow";
        this->show();
    }
}
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    painter->drawText(QPointF((sourcePoint.x() + destPoint.x())/2,(sourcePoint.y() + destPoint.y())/2 +1),"EdgeText");


}

QVariant Edge::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}
QRectF  Edge::boundingRect() const {
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}
