#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>

class Node;
//
//@brief в конструкторе (mainwindow.cpp) добавить
// GraphWidget *w = new GraphWidget();
//ui->tabWidget->addTab(w,"GraphWidgetDemo");
// (не забудьте об #include)
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
signals:

public slots:
    void zoomIn();
    void zoomOut();

};

#endif // GRAPHWIDGET_H
