#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QObject>
#include <QWidget>
#include  "gui/scheduletableview.h"
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include "models/scheduefilterproxymodel.h"
class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QAbstractTableModel *model = nullptr,QWidget *parent = nullptr);
    QGridLayout *grid;

signals:
//генерация расписания
void gen_schedule();

public slots:
    void apply_clicked();
private:
    QAbstractTableModel *sceduleModel;
    SchedueFilterProxyModel *proxyModel;
    QGroupBox *createSchedueFilters();
    ScheduleTableView *scheduleTable;
    //размещение кнопки
    QGridLayout *form;
    //кнопка собрать расписание
    QPushButton *gen_btn;
};

#endif // SCHEDULEWIDGET_H
