#include "graphwidget.h"

#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
#include "models/filterdata.h"
GraphWidget::GraphWidget(QWidget *parent): QGraphicsView(parent),scene(new QGraphicsScene(this))
{


    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 1000, 1000);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate); //reconsider
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    this->resize(400,400);
    //setMinimumSize(400, 400);

    //@brief
    //    Node *node1 = new Node (this,10,0,"Center",Qt::cyan);
    //    Node *node2 = new Node (this,10,0,"Center",Qt::gray);
    //    Node *node3 = new Node (this,10,0,"Center",Qt::red);
    //    Node *node4 = new Node (this,10,0,"Center",Qt::blue);
    //    Node *node5 = new Node (this,10,0,"Center",Qt::green);


    //    scene->addItem(node1);
    //    scene->addItem(node2);
    //    scene->addItem(node3);
    //    scene->addItem(node4);
    //    scene->addItem(node5);

    //    scene->addItem(new Edge(node1, node2));
    //    scene->addItem(new Edge(node2, node3));
    //    scene->addItem(new Edge(node2, node4));
    //    scene->addItem(new Edge(node2, node5));
    //    scene->addItem(new Edge(node5, node4));

    //    node1->setPos(200,200);
    //    node2->setPos(0+200,60+200);
    //    node3->setPos(20+200,10+200);
    //    node4->setPos(40+200,25+200);
    //    node5->setPos(10+200,-30+200);

    //    nodes.push_back(node1);
    //    nodes.push_back(node2);
    //    nodes.push_back(node3);
    //    nodes.push_back(node4);
    //    nodes.push_back(node5);

    //    readGraph(QPointF(200,200));

    qDebug()<<"Scene width"<<scene->width()<<" Scene height"<<scene->height();
}

void GraphWidget::buildNewGraph(QVector<QSet<QString> > data, QList<Lesson> lessons)
{
    //Создание вершин
    //nodeMatrix.clear();

    nodeMatrix.clear();
    //textNodes.clear();
    scene->clear();
    createTextNodes();
    qDebug()<<"data vector size"<<data.size();

    for (int i = 0; i<data.size();i++) {
        qDebug()<<data[i]<<data[i].size();
        qDebug()<<data[i].toList().at(0);
        QVector<QPointF> p = this->createLinePoint(data[i].size(),nodeSize,i);
        QHash <QString, Node*> hash_nodes;

        for (int q = 0 ;q<p.size();q++) {

            Node *node = new Node(this,nodeSize,i,data[i].toList().at(q),this->colorVector[i]);
            hash_nodes.insert(data[i].toList().at(q),node);

            scene->addItem(node);
            node->setPos(p[q]);
        }

        nodeMatrix.append(hash_nodes);

    }
    //Связывание
    qDebug()<<nodeMatrix.size();
    for (int curLesson = 0 ; curLesson<lessons.size(); curLesson++) {
        this->linkLessonsParts(lessons[curLesson]);
    }

}



void GraphWidget::updateGraph(QList<Lesson> &lessons)
{
    this->lessons = lessons;

}

void GraphWidget::hideAll()
{
    for (int slide= 0; slide < nodeMatrix.size(); ++slide) {
        for (QHash<QString,Node*>::iterator i =nodeMatrix[slide].begin(); i != nodeMatrix[slide].end(); ++i) {
            i.value()->hide();
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

    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut() {
    scaleView(1 / qreal(1.2));
}

void GraphWidget::resetFilter()
{
    //    foreach (Node * curNode, nodes) {
    //        curNode->show();
    //    }

    for (int slide= 0; slide < nodeMatrix.size(); ++slide) {
        for (QHash<QString,Node*>::iterator i =nodeMatrix[slide].begin(); i != nodeMatrix[slide].end(); ++i) {
            i.value()->show();
        }

    }

}

void GraphWidget::useFilter(FilterData &fdata)
{
    resetFilter();
    qDebug()<<"FraphUseFilter"<<fdata.data;

    for (int curSlide = 0 ;curSlide < fdata.data.size();curSlide++) {
        if (fdata.data[curSlide] != "None") {
            if (!filterBySlide(curSlide,fdata.data[curSlide])) {
                hideAll();
                break;
            }
        } else {
            qDebug()<<"None"<<curSlide;
        }
    }

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

QVector<QPointF> GraphWidget::createLinePoint(int lenght, double size, int slice)
{
    QVector<QPointF> p;
    QPointF start(size/2+slice*size*2,size+size);

    for (int i = 0; i<lenght;i++) {
        p.append(start);
        start.setY(start.y()+size*2);
    }
    return p;
}



bool GraphWidget::filterBySlide(int slide, QString data)
{
    qDebug()<<"Filters"<<data;
    Node * node = nullptr;
    for (QHash<QString,Node*>::iterator i =nodeMatrix[slide].begin(); i != nodeMatrix[slide].end(); ++i) {
        //qDebug()<<"COMPARE"<<QString::compare(i.value()->getData(),data,Qt::CaseInsensitive);
        //bool wtf = i.value()->getData();
        //qDebug()<<wtf;
        if (slide == 7) {
            qDebug()<<"Time"<<data;
        }
        if (i.value()->getData() != data) {
            i.value()->hide();
        } else  {
            qDebug()<<"Work"<<slide;
            node = i.value();
        }
    }
    int backID = slide;
    int forwardID = slide;
    while (backID != 0) {
        if(backID != nodeMatrix.size())
            leftFilterSlise(backID);
        backID--;
    }

    while (forwardID != nodeMatrix.size()) {
        if (forwardID != 0)
            rightFilterSlise(forwardID);
        forwardID++;
    }
    QList<Edge *> l = node->edges();
    bool canLife = false;
    for (Edge * e : l) {
        if (e->isVisible()) {
            canLife = true;
        }
    }
    if (canLife)
        return true;
    else
        return false;

}

void GraphWidget::leftFilterSlise(int slide)
{
    for (QHash<QString,Node*>::iterator i =nodeMatrix[slide].begin(); i != nodeMatrix[slide].end(); ++i) {

        QList<Edge *> l = i.value()->edges();
        bool canLife = false;
        for (Edge * e : l) {

            if ((e->sourceNode()->getSliceId() == i.value()->getSliceId())
                    && (e->sourceNode()->getPos() ==  i.value()->getPos()) && (e->isVisible())) {
                canLife = true;
            }
        }
        if (!canLife) {
            i.value()->hide();
        }
    }
}

void GraphWidget::rightFilterSlise(int slide)
{
    for (QHash<QString,Node*>::iterator i =nodeMatrix[slide].begin(); i != nodeMatrix[slide].end(); ++i) {

        QList<Edge *> l = i.value()->edges();
        bool canLife = false;
        for (Edge * e : l) {

            if ((e->destNode()->getSliceId() == i.value()->getSliceId())
                    && (e->destNode()->getPos() ==  i.value()->getPos())&& (e->isVisible())) {
                canLife = true;
            }
        }
        if (!canLife) {
            i.value()->hide();
        }
    }
}

void GraphWidget::linkLessonsParts(Lesson lesson)
{
    QVector<QString> lessonDataString;

    lessonDataString.append(lesson._group.name);

    lessonDataString.append((lesson._subject.name));

    lessonDataString.append(QString::number(lesson._cabinet.number));
    lessonDataString.append(QString::number(lesson._cabinet.floor));
    lessonDataString.append(QString::number(lesson._cabinet.building));

    lessonDataString.append(QString::number(lesson._lessonTime.parity));
    lessonDataString.append(lesson._receiveDay.find(lesson._lessonTime.dayOfWeek).value());
    lessonDataString.append(lesson._lessonTime.time.toString());
    qDebug()<<"lessonString"<<lessonDataString<<" "<<lessonDataString.size();
    for (int curSlide = 0; curSlide < nodeMatrix.size() - 1; ++curSlide) {
        //qDebug()<<"Cur curSlide"<<curSlide;
        //qDebug()<<"Cur curSlide"<<curSlide<<" slide_Node_id"<<nodeMatrix[curSlide].find(lessonDataString[curSlide]).value()->getSliceId();
        scene->addItem(new Edge(nodeMatrix[curSlide].find(lessonDataString[curSlide]).value(), nodeMatrix[curSlide+1].find(lessonDataString[curSlide+1]).value()));
    }
    //scene->addItem(new Edge(node1, node2));
}

void GraphWidget::createTextNodes()
{
    qDebug()<<"Text";
    QVector<QString> coll = {"Группа", "Предмет","Кабинет","Этаж","Корпус","Четность","День","Время"};
    for (int i = 0; i<coll.size();i++) {
        double mult = i*nodeSize*2;
        //QPointF p(nodeSize/2+mult,2*nodeSize);
        QPointF p(nodeSize/2+mult,nodeSize/2);
        Node * node= new Node(this,nodeSize,0,coll[i],Qt::transparent,Qt::transparent);
        node->setPos(p);
        scene->addItem(node);
        //textNodes.append(node);
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
