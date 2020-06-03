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

    void buildNewGraph(QVector<QSet<QString> > data, QList<Lesson> lessons);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    QGraphicsScene *scene;
    QVector<QPointF> createClusterPoints(QPointF &center,int radius,int size) const;

    void scaleView(qreal scaleFactor);
    QVector<QColor> colorVector = {Qt::red,Qt::green,Qt::yellow,Qt::white,Qt::cyan,Qt::magenta,Qt::lightGray,Qt::blue};
    QVector<QPointF> createLinePoint(int lenght, double size, int slice);

    void filterBySlide(int slide,QString data);
    void leftFilterSlise(int slide);
    void rightFilterSlise(int slide);
    void linkLessonsParts(Lesson lesson);
    QList<Lesson> lessons;
    QVector<QHash<QString,Node*>> nodeMatrix;
    double nodeSize = 60;

signals:

public slots:
    void zoomIn();
    void zoomOut();
    void resetFilter();
    void useFilter(FilterData &fdata);
    void updateGraph(QList<Lesson> &lessons);



};

#endif // GRAPHWIDGET_H
