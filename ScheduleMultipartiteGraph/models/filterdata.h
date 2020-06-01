#ifndef FILTERDATA_H
#define FILTERDATA_H

#include <QString>
#include <QSet>
#include <QVector>
#include <QHash>
class FilterData
{
public:
    QString groupNumber;
    QString someData1;

    FilterData();

};

class DataForFilter {

public:
    DataForFilter();
    QVector<QSet<QString>> data;
    QHash<int,QString> receiveDay;



};

#endif // FILTERDATA_H
