#include "scheduletableabstractmodule.h"
#include <QDebug>

ScheduleTableAbstractModule::ScheduleTableAbstractModule(QObject *parent):
    QAbstractTableModel(parent){

}

//ScheduleTableAbstractModule::ScheduleTableAbstractModule(const QList<TestLesson> &dataList,
//                                                         QObject* parent):
//    QAbstractTableModel(parent)
//{
//    this->m_dataSet = dataList;
//    collums = m_dataSet[0].coll; //...

//}

ScheduleTableAbstractModule::ScheduleTableAbstractModule(const QList<Lesson> &dataList, QObject *parent)
{
    this->m_dataSet = dataList;
    qDebug()<<"size"<<m_dataSet[0].coll;
    collums = m_dataSet[0].coll; //...
}

int ScheduleTableAbstractModule::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->collums.size();
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
        // const TestLesson& planet = m_dataSet.at(index.row());
        const Lesson& planet = m_dataSet.at(index.row());
        switch (index.column()) {
        case 0:
            return planet._group.name;
            //return planet.m_name;
        case 1:
            return planet._subject.name;
            //return planet.m_data1;
        case 2:
            return planet._cabinet.number;
            //return planet.m_data2;
        case 3:
            return planet._cabinet.floor;
            //return planet.m_data2;
        case 4:
            return planet._cabinet.building;
            //return planet.m_data2;
        case 5:
            return planet._lessonTime.parity;
        case 6:
            return planet._receiveDay.find(planet._lessonTime.dayOfWeek).value();
        case 7:
            return planet._lessonTime.time;
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
