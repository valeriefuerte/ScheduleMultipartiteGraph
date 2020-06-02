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
#include <QComboBox>
#include "models/filterdata.h"

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QAbstractTableModel *model = nullptr,QWidget *parent = nullptr);
    QGridLayout *grid;

    //filter data
    QComboBox *groupComboBox;

    QComboBox *subjectComboBox;

    QComboBox *floorComboBox;
    QComboBox *buildingComboBox;
    QComboBox *numberComboBox;

    QComboBox *timeComboBox;
    QComboBox *dayComboBox;
    QComboBox *parityComboBox;


    //grilay
signals:
    //генерация расписания
    void gen_schedule();

public slots:
    //нажатие кнопки генерация модели
    void apply_clicked();

    void updateModel(QAbstractTableModel *model);

    void insertFilterDataVariants(QVector<QSet<QString>> dataForFilters);
    FilterData takeDataFromFilters();
private:
    QAbstractTableModel *sceduleModel;
    SchedueFilterProxyModel *proxyModel;
    QGroupBox *createSchedueFilters();
    ScheduleTableView *scheduleTable;
    //размещение кнопки
    QGridLayout *form;
    //кнопка собрать расписание
    QPushButton *gen_btn;

    //QHash<int,QString> receiveDay; //
};

#endif // SCHEDULEWIDGET_H
