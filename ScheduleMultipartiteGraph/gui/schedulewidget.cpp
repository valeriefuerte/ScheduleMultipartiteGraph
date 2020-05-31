#include "schedulewidget.h"
#include <QHBoxLayout>
#include <QGroupBox>
ScheduleWidget::ScheduleWidget(QAbstractTableModel *model, QWidget *parent) : QWidget(parent)
{
    proxyModel = new SchedueFilterProxyModel;
    proxyModel->setSourceModel(model);
    scheduleTable = new ScheduleTableView(proxyModel,this);
    scheduleTable->resize(parent->width(),parent->height());
    grid = new QGridLayout;
    grid->addWidget(scheduleTable,0,0);
    grid->addWidget(createSchedueFilters(),1,0);
    setLayout(grid);
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

