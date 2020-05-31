#ifndef PLANETTABLEMODEL_H
#define PLANETTABLEMODEL_H

#include <QAbstractTableModel>
#include "planet.h"
#include <QColor>

class PlanetTableModel : public QAbstractTableModel
{
public:

    PlanetTableModel(QObject* parent = 0);
    PlanetTableModel(const QList<Planet>& planetList,
                         QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data (const QModelIndex & index,
                   int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
private:
    QList<Planet> m_planetList;
};

#endif // EARTHQUAKETABLEMODEL_H
