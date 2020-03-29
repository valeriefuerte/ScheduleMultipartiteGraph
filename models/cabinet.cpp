#include "cabinet.h"

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

    this->id = items.value("id").toInt();
    this->number = items.value("number").toInt();
    this->floor = items.value("floor").toInt();
    this->building = items.value("building").toInt();
}
