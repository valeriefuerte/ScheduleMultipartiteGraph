#include "table_model.h"
#include <QTableView>
#include <QDebug>



int StringListModel::rowCount(const QModelIndex &parent) const
 {
     return stringList.count();
 }

QVariant StringListModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= stringList.size())
         return QVariant();

     if (role == Qt::DisplayRole)
         return stringList.at(index.row());
     else
         return QVariant();
 }

QVariant StringListModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
 {
     qint8 i = 0;
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
         return QString().arg(section);
     else
         return QString("*_*").arg(section);
 }
Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;
     return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
 }
bool StringListModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool StringListModel::insertRows(int position, int rows, const QModelIndex &parent)
 {
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         stringList.insert(position, "");
     }

     endInsertRows();
     return true;
 }
bool StringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }
    endRemoveRows();
    return true;
}


