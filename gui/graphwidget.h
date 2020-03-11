#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>

class Node;


class GraphWidget: public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
private:

signals:

public slots:
    void zoomIn();
    void zoomOut();

};

#endif // GRAPHWIDGET_H
