#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent),scene(new QGraphicsScene(this))
{


    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate); //reconsider
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    //setMinimumSize(400, 400);

    //@brief
    Node *node1 = new Node (this,15,Qt::cyan);
    Node *node2 = new Node (this,15,Qt::gray);
    Node *node3 = new Node (this,15,Qt::red);
    Node *node4 = new Node (this,15,Qt::blue);
    Node *node5 = new Node (this,15,Qt::green);


    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(node5);

    scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));
    scene->addItem(new Edge(node2, node4));
    scene->addItem(new Edge(node2, node5));
    scene->addItem(new Edge(node5, node4));

    node1->setPos(0,0);
    node2->setPos(0,60);
    node3->setPos(20,10);
    node4->setPos(40,25);
    node5->setPos(10,-30);

    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);
    nodes.push_back(node5);

    readGraph(QPointF(-30,-20));


}

void GraphWidget::readGraph(QPointF center)
{


    QVector<QPointF> test = createClusterPoints(center,105,7);
    foreach (QPointF p, test) {

        QVector<QPointF> test2 = createClusterPoints(p,20,5);
        foreach (QPointF p2, test2) {
            Node *node = new Node(this);
            scene->addItem(node);
            node->setPos(p2.x(),p2.y());
            nodes.push_back(node);
        }
    }
}
void  GraphWidget::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);


    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);

}

QVector<QPointF> GraphWidget::createClusterPoints(QPointF &center, int radius, int size) const
{
    QVector <QPointF> points;
    for (int i = 0; i < size; ++i) {
        double angle_deg = 360/size * i;

        double angle_rad = M_PI / 180 * angle_deg;

        points.append(QPointF (center.x()+radius*cos(angle_rad),center.y()+radius*sin(angle_rad)));

    }
    return points;
}
void GraphWidget::zoomIn() {

}

void GraphWidget::zoomOut() {

}

void GraphWidget::resetFilter()
{
    foreach (Node * curNode, nodes) {
        curNode->show();
    }
}
void GraphWidget::keyPressEvent(QKeyEvent *event)
{

}
