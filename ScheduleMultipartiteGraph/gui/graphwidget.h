#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>

#include "edge.h"
#include "node.h"

class Node;
class FilterData;
class GraphWidget: public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = nullptr);
    void readGraph(QPointF center); // WORK IN PROGRESS
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
private:
    QGraphicsScene *scene;
    QVector<QPointF> createClusterPoints(QPointF &center,int radius,int size) const;
    QVector<Node*> nodes;
signals:

public slots:
    void zoomIn();
    void zoomOut();
    void resetFilter();
    void useFilter(FilterData &data);

};

#endif // GRAPHWIDGET_H
