#ifndef SCHEDULETABLEABSTRACTMODULE_H
#define SCHEDULETABLEABSTRACTMODULE_H

#include <QObject>
#include <QAbstractTableModel>
#include "models/TestLesson.h"

class ScheduleTableAbstractModule: public QAbstractTableModel
{
public:
    QVector<QString> collums;
    ScheduleTableAbstractModule(QObject* parent = 0);
    ScheduleTableAbstractModule(const QList<Lesson>& dataList,
                                QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data (const QModelIndex & index,
                   int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
private:
    QList<Lesson> m_dataSet;
};

#endif // SCHEDULETABLEABSTRACTMODULE_H
