#include "groupstudents.h"

GroupStudents::GroupStudents(QString name)
{
    this->name = name;
}

QString GroupStudents::getClassName() {
    return QString("GroupStudents");
}

QJsonObject GroupStudents::toJson() {
    QJsonObject items;
    items.insert("id", QString("%1").arg(this->id));
    items.insert("name", QString("%1").arg(this->name));

    return items;
}

void GroupStudents::fromJson(QJsonObject items) {

    this->id = items.value("id").toInt();
    this->name = items.value("name").toString();
}

QString GroupStudents::toString() {
    return QString("");
}
