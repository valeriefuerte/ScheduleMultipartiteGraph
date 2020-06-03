#include "schedulewidget.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFormLayout>
#include <QDebug>

ScheduleWidget::ScheduleWidget(QAbstractTableModel *model, QWidget *parent) : QWidget(parent)
{

    QPushButton *gen_btn = new QPushButton("Собрать расписание");
    gen_btn->setMaximumWidth(170);
    form = new QGridLayout();


    proxyModel = new SchedueFilterProxyModel;
    proxyModel->setSourceModel(model);
    scheduleTable = new ScheduleTableView(proxyModel,this);
    scheduleTable->resize(parent->width(),parent->height());
    grid = new QGridLayout;

    form->addWidget(gen_btn,0,3);
    grid->addWidget(scheduleTable,0,0);
    grid->addWidget(createSchedueFilters(),1,0);
    //расположение кнопки генерация расписания
    grid->addLayout(form,2,0,Qt::AlignCenter);
    setLayout(grid);

    connect(gen_btn,SIGNAL(clicked()),this,SLOT(apply_clicked()));

    // connect for filters
    connect(groupComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);
    connect(subjectComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);

    connect(numberComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);
    connect(floorComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);
    connect(buildingComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);

    connect(parityComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);
    connect(dayComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);
    connect(timeComboBox,&QComboBox::currentTextChanged,this,&ScheduleWidget::filtersChanged);

}

void ScheduleWidget::updateModel(QAbstractTableModel *model)
{
    this->sceduleModel = model;
    proxyModel->setSourceModel(sceduleModel);
    scheduleTable->changeModel(proxyModel);
}

void ScheduleWidget::insertFilterDataVariants(QVector<QSet<QString> > dataForFilters)
{
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

void ScheduleWidget::filtersChanged()
{
    FilterData data = this->takeDataFromFilters();
    this->proxyModel->useFilters(data);
    qDebug()<<"SchedueFilters";
}

FilterData ScheduleWidget::takeDataFromFilters()
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

QGroupBox * ScheduleWidget::createSchedueFilters()
{
    QGroupBox *box = new QGroupBox("Фильры");
    QLabel *label = new QLabel("Выбери параметры");
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

void ScheduleWidget::apply_clicked(){
    emit gen_schedule();
}

