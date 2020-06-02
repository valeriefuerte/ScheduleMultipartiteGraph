#include "scheduefilterproxymodel.h"


SchedueFilterProxyModel::SchedueFilterProxyModel(QObject *parent): QSortFilterProxyModel(parent)

{

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

//    QModelIndex indG = sourceModel()->index(source_row,
//                                               1, source_parent);
//    QModelIndex indD = sourceModel()->index(source_row,
//                                               2, source_parent);
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
