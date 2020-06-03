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
    //gen_btn = new QPushButton("Создать граф",this);
    //connect(gen_btn,SIGNAL(clicked()),this,SLOT(apply_clicked()));
    grid->addWidget(graphWidget,1,0);
    //grid->addWidget(createMenu(),0,0);
    grid->addWidget(createSchedueFilters(),2,0);
    //grid->addWidget(gen_btn,3,0);
    setLayout(grid);

    connect(groupComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);
    connect(subjectComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);

    connect(numberComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);
    connect(floorComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);
    connect(buildingComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);

    connect(parityComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);
    connect(dayComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);
    connect(timeComboBox,&QComboBox::currentTextChanged,this,&VisualizationWidget::filtersChanged);



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

void VisualizationWidget::insertFilterDataVariants(QVector<QSet<QString> > dataForFilters)
{
    /*for (int i=1; i<groupComboBox->count(); i++){
        groupComboBox->removeItem(i);
     }

    for (int i=1; i<subjectComboBox->count(); i++){
        subjectComboBox->removeItem(i);
     }

    for (int i=1; i<numberComboBox->count(); i++){
        numberComboBox->removeItem(i);
     }

    for (int i=1; i<floorComboBox->count(); i++){
        floorComboBox->removeItem(i);
     }

    for (int i=1; i<buildingComboBox->count(); i++){
        buildingComboBox->removeItem(i);
     }

    for (int i=1; i<parityComboBox->count(); i++){
        parityComboBox->removeItem(i);
     }

    for (int i=1; i<dayComboBox->count(); i++){
        dayComboBox->removeItem(i);
     }

    for (int i=1; i<timeComboBox->count(); i++){
        timeComboBox->removeItem(i);
     }*/


    QVector<QStringList> stringLists;
    for (int i = 0; i < dataForFilters.size(); ++i) {
        QList<QString> list = dataForFilters[i].toList();
        //list.push_front("None");
        stringLists.append(QStringList(list));
    }
    groupComboBox->addItems(stringLists[0]);
    subjectComboBox->addItems(stringLists[1]);
    numberComboBox->addItems(stringLists[2]);
    floorComboBox->addItems(stringLists[3]);
    buildingComboBox->addItems(stringLists[4]);
    parityComboBox->addItems(stringLists[5]);
    dayComboBox->addItems(stringLists[6]);
    timeComboBox->addItems(stringLists[7]);



}

FilterData VisualizationWidget::takeDataFromFilters()
{
    FilterData filterData;

    QVector<QString> data;
    data.append(groupComboBox->currentText());
    data.append(subjectComboBox->currentText());
    data.append(numberComboBox->currentText());
    data.append(floorComboBox->currentText());
    data.append(buildingComboBox->currentText());
    data.append(parityComboBox->currentText());
    data.append(dayComboBox->currentText());
    data.append(timeComboBox->currentText());


    qDebug()<<data;
    filterData.data = data;
    return filterData;

}

void VisualizationWidget::filtersChanged()
{
    qDebug()<<"SchedueFilters_graph";
    FilterData data = this->takeDataFromFilters();
    graphWidget->useFilter(data);
}

void VisualizationWidget::apply_clicked()
{
    emit gen_graph();
}



void VisualizationWidget::resetGraphWidget()
{

}

void VisualizationWidget::setupGraph( QVector<QSet<QString>> data,QList<Lesson> lessons)
{
    qDebug()<<"Set up graph";
    graphWidget->buildNewGraph(data,lessons);
}

QGroupBox* VisualizationWidget::createMenu()
{
    QGroupBox *nmenu = new QGroupBox(this);
    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *filterButton = new QPushButton("Filter");


    connect(resetButton,&QPushButton::clicked,graphWidget,&GraphWidget::resetFilter);
    connect(filterButton,&QPushButton::clicked, [this] () {
        FilterData data = this->takeDataFromFilters();
        graphWidget->useFilter(data);
    });
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
    QHBoxLayout *vbox = new QHBoxLayout;


    groupComboBox = new QComboBox();
    subjectComboBox = new QComboBox();
    floorComboBox = new QComboBox();
    buildingComboBox = new QComboBox();
    numberComboBox = new QComboBox();
    timeComboBox = new QComboBox();
    dayComboBox = new QComboBox();
    parityComboBox = new QComboBox();

    groupComboBox->addItem("None");
    subjectComboBox->addItem("None");
    floorComboBox ->addItem("None");
    buildingComboBox ->addItem("None");
    numberComboBox ->addItem("None");
    timeComboBox ->addItem("None");
    dayComboBox ->addItem("None");
    parityComboBox ->addItem("None");

    vbox->addWidget(label);

    vbox->addWidget(groupComboBox);
    vbox->addWidget(subjectComboBox);
    vbox->addWidget(numberComboBox);
    vbox->addWidget(floorComboBox);
    vbox->addWidget(buildingComboBox);
    vbox->addWidget(parityComboBox);
    vbox->addWidget(dayComboBox);
    vbox->addWidget(timeComboBox);



    box->setLayout(vbox);
    return box;
}
