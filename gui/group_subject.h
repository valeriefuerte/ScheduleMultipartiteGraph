#ifndef GROUP_SUBJECT_H
#define GROUP_SUBJECT_H

#include "QMultiHash"
#include "models/tablelistmodel.h"
#include "mainwindow.h"

class GroupSubject : public QObject
{

public:
    //данные таблицы из вкладки "Данные"
    void receiveGroup(QStringList*, MainWindow*);
    TableListModel *gr_sub_model;
    MainWindow *object;

private:
    void visualRows(QTableView *table, TableListModel *model);
public slots:
    void customGroupSubjectMenuRequested(const QPoint &pos);
    void slotAddSG();
};

#endif // GROUP_SUBJECT_H
