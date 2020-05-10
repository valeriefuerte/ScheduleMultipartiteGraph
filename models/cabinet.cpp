#include "cabinet.h"
#include <QDebug>

Cabinet::Cabinet(int number, int floor, int building)
{
    this->number = number;
    this->floor = floor;
    this->building = building;
}

QString Cabinet::getClassName() {
    return QString("Cabinet");
}

QJsonObject Cabinet::toJson() {
    QJsonObject items;
    items.insert("id", QString("%1").arg(this->id));
    items.insert("number", QString("%1").arg(this->number));
    items.insert("floor", QString("%1").arg(this->floor));
    items.insert("building", QString("%1").arg(this->building));

    return items;
}

void Cabinet::fromJson(QJsonObject items) {
    this->id = items.value("id").toString().toInt();
    this->number = items.value("number").toString().toInt();
    this->floor = items.value("floor").toString().toInt();
    this->building = items.value("building").toString().toInt();
}

QString Cabinet::toString() {
    return QString("id: %1, number: %2, floor: %3, building: %4").arg(this->id).arg(this->number).arg(this->floor).arg(this->building);
}

bool Cabinet::operator== (const Cabinet &object)
{
    return (
               (this->building == object.building || object.building != 0)
            && (this->floor == object.floor || object.floor == 0)
            && (this->number == object.number ||  object.number == 0)
    );
}
