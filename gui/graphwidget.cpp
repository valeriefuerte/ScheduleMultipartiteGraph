#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    //setMinimumSize(400, 400);


    Node *node1 = new Node (this);
    Node *node2 = new Node (this);

    Node *node3 = new Node (this,20,Qt::red);
    Node *node4 = new Node (this,20,Qt::blue);

    Node *node5 = new Node (this,20,Qt::green);


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
    node2->setPos(0,50);
    node3->setPos(20,10);
    node4->setPos(40,25);
    node5->setPos(0,-30);


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
void GraphWidget::zoomIn() {

}

void GraphWidget::zoomOut() {

}
void GraphWidget::keyPressEvent(QKeyEvent *event)
{

}
