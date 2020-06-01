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

    grid->addLayout(form,2,0,Qt::AlignCenter);
    setLayout(grid);

    connect(gen_btn,SIGNAL(clicked()),this,SLOT(apply_clicked()));
}

QGroupBox * ScheduleWidget::createSchedueFilters()
{
    QGroupBox *box = new QGroupBox("Filters");


    QLabel *label = new QLabel("FilterPlaceHolders");

    QVBoxLayout *vbox = new QVBoxLayout;



    vbox->addWidget(label);

    box->setLayout(vbox);
    return box;
}

void ScheduleWidget::apply_clicked(){
    emit gen_schedule();
}

