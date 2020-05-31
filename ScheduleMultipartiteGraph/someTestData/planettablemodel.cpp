#include "planettablemodel.h"

PlanetTableModel::PlanetTableModel(QObject *parent):
    QAbstractTableModel(parent){

}

PlanetTableModel::PlanetTableModel(const QList<Planet> &planetList,
                                           QObject* parent):
    QAbstractTableModel(parent)
{
    this->m_planetList = planetList;
}

int PlanetTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

int PlanetTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_planetList.size();
}

QVariant PlanetTableModel::data (const QModelIndex & index,
               int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_planetList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const Planet& planet = m_planetList.at(index.row());
        switch (index.column()) {
        case 0:
            return planet.m_name;
        case 1:
            return planet.m_gravity;
        case 2:
            return planet.m_density;
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

QVariant PlanetTableModel::headerData(int section,
                                          Qt::Orientation orientation,
                    int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Planet");
        case 1:
            return tr("Gravity [m/s^2]");
        case 2:
            return tr("Density [g/cm^3]");
        default:
            return QVariant();
        }
    }
    return section + 1;
}
