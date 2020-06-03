#include "scheduefilterproxymodel.h"
#include <QDebug>

SchedueFilterProxyModel::SchedueFilterProxyModel(QObject *parent): QSortFilterProxyModel(parent)

{
    QVector<QString> nonePlace;
    nonePlace.fill("None",data.coll.size());
    data.data = nonePlace;
}

//void SchedueFilterProxyModel::setMinGravity(double minGravity){
//    if(m_minGravity != minGravity)
//        m_minGravity = minGravity;
//    invalidateFilter();
//}

//void SchedueFilterProxyModel::setMinDensity(double minDensity){
//    if(m_minDensity != minDensity)
//        m_minDensity = minDensity;
//    invalidateFilter();
//}

bool SchedueFilterProxyModel::filterAcceptsRow(int source_row,
                                               const QModelIndex &source_parent) const{

    //QVector<QModelIndex> vectorIndex;
    for (int i = 0;i<data.data.size();i++) {
       // vectorIndex.append(sourceModel()->index(source_row,
       //                                         i, source_parent));
        QModelIndex model_index =sourceModel()->index(source_row,i, source_parent);
        QString opp = data.data[i];
       if ((opp != sourceModel()->data(model_index).toString()) && (opp !="None")) {
            return false;
        }
    }
    return true;
    //    if(sourceModel()->data(indG).toDouble() < m_minGravity ||
    //            sourceModel()->data(indD).toDouble() < m_minDensity)
    //        return false;
    //    return true;

}

QVariant SchedueFilterProxyModel::headerData(int section, Qt::Orientation orientation,
                                             int role) const {
    return sourceModel()->headerData(section, orientation,
                                     role);
}

void SchedueFilterProxyModel::useFilters(FilterData &data)
{
    this->data =data;
    invalidateFilter();
}
