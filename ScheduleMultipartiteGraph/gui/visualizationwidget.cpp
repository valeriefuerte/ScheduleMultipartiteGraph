#include "visualizationwidget.h"

#include <QHBoxLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QLabel>
VisualizationWidget::VisualizationWidget(QWidget *parent) : QWidget(parent)//,


{
    grid = new QGridLayout;
    graphWidget = new GraphWidget(this);
    gen_btn = new QPushButton("Создать граф",this);
    connect(gen_btn,SIGNAL(clicked()),this,SLOT(apply_clicked()));
    grid->addWidget(graphWidget,0,0);
    grid->addWidget(createMenu(),1,0);
    grid->addWidget(createSchedueFilters(),2,0);
    grid->addWidget(gen_btn,3,0);
    setLayout(grid);




    //qDebug()<<"VisualWidget"<<this->width()<<" "<<this->height()<<" "<<this->geometry().center();
    //qDebug()<<"GraphWidget"<<this->graphWidget->width()<<" "<<this->graphWidget->height()<<" "<<this->graphWidget->geometry().center();

}

void VisualizationWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    painter.setPen(QPen(Qt::blue));
    painter.drawRect(0,0,this->width(),this->height());
    painter.drawPoint(this->geometry().center());
    painter.drawLine(QPoint(this->width()/2,0),QPoint(this->width()/2,this->height()));

    graphWidget->move(this->width()/2 - this->graphWidget->width()/2,this->height()/2 - this->graphWidget->height()/2);

    //qDebug()<<"VisualWidget"<<this->width()<<" "<<this->height()<<" "<<this->geometry().center();
    //qDebug()<<"GraphWidget"<<this->graphWidget->width()<<" "<<this->graphWidget->height()<<" "<<this->graphWidget->geometry().center();
}

void VisualizationWidget::apply_clicked()
{
    emit gen_graph();
}



void VisualizationWidget::resetGraphWidget()
{

}

void VisualizationWidget::setupGraph(DataForFilter &data,QList<Lesson> lessons)
{
    qDebug()<<"Set up graph";
}

QGroupBox* VisualizationWidget::createMenu()
{
    QGroupBox *nmenu = new QGroupBox(this);
    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *filterButton = new QPushButton("Filter");


    connect(resetButton,&QPushButton::clicked,graphWidget,&GraphWidget::resetFilter);
    //    connect(filterButton,&QPushButton::clicked, [this] () {
    //        FilterData data =filter->getFilterData();
    //        graphWidget->useFilter(data);
    //    });
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(resetButton);
    layout->addWidget(filterButton);
    nmenu->setLayout(layout);
    return nmenu;

}

//void VisualizationWidget::updateRepo(RepositoryTemplate<Cabinet> repoCabinets, RepositoryTemplate<GroupStudents> repoGroupStudents, RepositoryTemplate<LessonTime> repoLessonTime, RepositoryTemplate<Subject> repoSubjects)
//{
//    this->repoCabinets = repoCabinets;
//    this->repoGroupStudents = repoGroupStudents;
//    this->repoLessonTime = repoLessonTime;
//    this->repoSubjects = repoSubjects;
//}

QGroupBox * VisualizationWidget::createSchedueFilters()
{
    QGroupBox *box = new QGroupBox("Filters");
    QLabel *label = new QLabel("FilterPlaceHolders");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label);
    box->setLayout(vbox);
    return box;
}
