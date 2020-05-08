#include "tablelistmodel.h"
#include <QTableView>
#include <QDebug>



int TableListModel::rowCount(const QModelIndex &parent) const
 {
     return stringList.count();
 }

QVariant TableListModel::data(const QModelIndex &index, int role) const
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

QVariant TableListModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
         return QString().arg(section);
     else
         return QString("%1").arg(section);
 }
Qt::ItemFlags TableListModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;
     return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
 }
bool TableListModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool TableListModel::insertRows(int position, int rows, const QModelIndex &parent)
 {
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         stringList.insert(position, "");
     }

     endInsertRows();
     return true;
 }
bool TableListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }
    endRemoveRows();
    return true;
}


