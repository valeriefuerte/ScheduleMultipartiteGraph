#include "visualizationwidget.h"

#include <QHBoxLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsProxyWidget>
#include <QDebug>
VisualizationWidget::VisualizationWidget(QWidget *parent) : QWidget(parent),
    graphWidget(new GraphWidget(this)),
    menu(createMenu()),
    filter(new FilterWidget(this))//,
  // visualGraphLayout(new QBoxLayout(QBoxLayout::LeftToRight,this))


{
    qDebug()<<"VisualWidget"<<this->width()<<" "<<this->height()<<" "<<this->geometry().center();
    qDebug()<<"GraphWidget"<<this->graphWidget->width()<<" "<<this->graphWidget->height()<<" "<<this->graphWidget->geometry().center();

}

void VisualizationWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    painter.setPen(QPen(Qt::blue));
    painter.drawRect(0,0,this->width(),this->height());
    painter.drawPoint(this->geometry().center());
    painter.drawLine(QPoint(this->width()/2,0),QPoint(this->width()/2,this->height()));

    graphWidget->move(this->width()/2 - this->graphWidget->width()/2,this->height()/2 - this->graphWidget->height()/2);
    filter->move(0,this->height()/2 - this->filter->height()/2);
    //qDebug()<<"VisualWidget"<<this->width()<<" "<<this->height()<<" "<<this->geometry().center();
    //qDebug()<<"GraphWidget"<<this->graphWidget->width()<<" "<<this->graphWidget->height()<<" "<<this->graphWidget->geometry().center();
}



void VisualizationWidget::resetGraphWidget()
{

}

QGroupBox* VisualizationWidget::createMenu()
{
    QGroupBox *nmenu = new QGroupBox(this);
    QPushButton *resetButton = new QPushButton("RESET");
    QPushButton *filterButton = new QPushButton("Filter");


    connect(resetButton,&QPushButton::clicked,graphWidget,&GraphWidget::resetFilter);
    connect(filterButton,&QPushButton::clicked, [this] () {
        FilterData data =filter->getFilterData();
        graphWidget->useFilter(data);
    });
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(resetButton);
    layout->addWidget(filterButton);
    nmenu->setLayout(layout);
    return nmenu;

}
