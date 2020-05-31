#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QObject>
#include <QWidget>
#include  "gui/scheduletableview.h"
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include "models/scheduefilterproxymodel.h"
class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QAbstractTableModel *model = nullptr,QWidget *parent = nullptr);
    QGridLayout *grid;

signals:

public slots:
    void updateModel(QAbstractTableModel *model);
private:
    QAbstractTableModel *sceduleModel;
    SchedueFilterProxyModel *proxyModel;
    QGroupBox *createSchedueFilters();
    ScheduleTableView *scheduleTable;
};

#endif // SCHEDULEWIDGET_H
