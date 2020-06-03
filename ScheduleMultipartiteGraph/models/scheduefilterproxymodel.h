#ifndef SCHEDUEFILTERPROXYMODEL_H
#define SCHEDUEFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "models/filterdata.h"
class SchedueFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SchedueFilterProxyModel(QObject* parent = 0);
    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    FilterData data;
public slots:
    void useFilters(FilterData &data);
private:

};

#endif // SCHEDUEFILTERPROXYMODEL_H
