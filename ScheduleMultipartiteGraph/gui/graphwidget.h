#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>
#include "models/Lesson.h"
#include "edge.h"
#include "node.h"

class Node;
class FilterData;
class GraphWidget: public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    QGraphicsScene *scene;
    QVector<QPointF> createClusterPoints(QPointF &center,int radius,int size) const;
    QVector<Node*> nodes;
    void scaleView(qreal scaleFactor);
    QVector<QColor> colorVector = {Qt::red,Qt::green,Qt::yellow,Qt::white};
    QVector<QPointF> createLinePoint(int lenght,int side,int radius);
    void leftFilterSlise(int slide);
    void rightFilterSlise(int slide);

    QList<Lesson> lessons;

signals:

public slots:
    void zoomIn();
    void zoomOut();
    void resetFilter();
    void useFilter(FilterData &data);
    void readGraph(QPointF center); // WORK IN PROGRESS
    void updateGraph(QList<Lesson> &lessons);


};

#endif // GRAPHWIDGET_H
