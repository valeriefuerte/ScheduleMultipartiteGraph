#include "scheduletableabstractmodule.h"


ScheduleTableAbstractModule::ScheduleTableAbstractModule(QObject *parent):
    QAbstractTableModel(parent){

}

ScheduleTableAbstractModule::ScheduleTableAbstractModule(const QList<Lesson> &dataList,
                                                         QObject* parent):
    QAbstractTableModel(parent)
{
    this->m_dataSet = dataList;
    collums = m_dataSet[0].coll; //... ксли список пустой - вызвать исключение ?

}

int ScheduleTableAbstractModule::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->collums.size(); //как лучше сделать ?
}

int ScheduleTableAbstractModule::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_dataSet.size();
}

QVariant ScheduleTableAbstractModule::data (const QModelIndex & index,
                                            int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_dataSet.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const Lesson& planet = m_dataSet.at(index.row());
        switch (index.column()) {
        case 0:
            return planet.m_name;
        case 1:
            return planet.m_data1;
        case 2:
            return planet.m_data2;
        default:
            return QVariant();
        }
    }
    else if (role == Qt::TextAlignmentRole){
        if (index.column() == 0)
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        else
            return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant ScheduleTableAbstractModule::headerData(int section,
                                                 Qt::Orientation orientation,
                                                 int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section>collums.size())
            return QVariant();
        else
            return this->collums[section];

    }

    return section + 1;
}
