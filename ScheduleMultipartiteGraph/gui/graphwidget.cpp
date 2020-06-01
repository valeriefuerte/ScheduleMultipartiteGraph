#include "graphwidget.h"

#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent),scene(new QGraphicsScene(this))
{


    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 400, 400);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate); //reconsider
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    this->resize(400,400);
    //setMinimumSize(400, 400);

    //@brief
    Node *node1 = new Node (this,10,0,"Center",Qt::cyan);
    Node *node2 = new Node (this,10,0,"Center",Qt::gray);
    Node *node3 = new Node (this,10,0,"Center",Qt::red);
    Node *node4 = new Node (this,10,0,"Center",Qt::blue);
    Node *node5 = new Node (this,10,0,"Center",Qt::green);


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

    node1->setPos(200,200);
    node2->setPos(0+200,60+200);
    node3->setPos(20+200,10+200);
    node4->setPos(40+200,25+200);
    node5->setPos(10+200,-30+200);

    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);
    nodes.push_back(node5);

    readGraph(QPointF(200,200));

    qDebug()<<"Scene width"<<scene->width()<<" Scene height"<<scene->height();
}

void GraphWidget::readGraph(QPointF center)
{


    QVector<QPointF> test = createClusterPoints(center,105,3);
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

void GraphWidget::updateGraph(QList<Lesson> &lessons)
{
    this->lessons = lessons;

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

    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut() {
    scaleView(1 / qreal(1.2));
}

void GraphWidget::resetFilter()
{
    foreach (Node * curNode, nodes) {
        curNode->show();
    }
}

void GraphWidget::useFilter(FilterData &data)
{
    qDebug()<<"FraphUseFilter";
}
void GraphWidget::keyPressEvent(QKeyEvent *event)
{

}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

QVector<QPointF> GraphWidget::createLinePoint(int lenght, int size, int slice)
{
    QVector<QPointF> p;
    QPointF start(size+2+slice*20,size+2);

    for (int i = 0; i<lenght;i++) {
        p.append(start);
        start.setY(start.y()+size*2);
    }
    return p;
}

QVector<Node *> GraphWidget::createLineNode(QVector<QPointF> &points,int slice,int size,QString data)
{
    QVector<Node *> lineNodes;
    foreach (QPointF p, points) {
        lineNodes.append(new Node(this));
    }
    return lineNodes;
}

void GraphWidget::leftFilterSlise(int slide)
{
    if (slide > 0) {

    }
}

void GraphWidget::rightFilterSlise(int slide)
{
    if (slide<8) {

    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
