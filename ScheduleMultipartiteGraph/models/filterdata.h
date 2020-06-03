#ifndef FILTERDATA_H
#define FILTERDATA_H

#include <QString>
#include <QSet>
#include <QVector>
#include <QHash>
class FilterData
{
public:
    FilterData();
    FilterData(QVector<QString> data);
    QVector<QString> data;
    QVector<QString> coll = {"Группа", "Предмет","Кабинет","Этаж","Корпус","Четность","День недели","Время"};


};



#endif // FILTERDATA_H
