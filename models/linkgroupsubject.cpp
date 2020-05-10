#include "linkgroupsubject.h"

LinkGroupSubject::LinkGroupSubject(int grId,int subId, int academicHours)
{
    this->groupId=grId;
    this->subjectId=subId;
    this->academicHours=academicHours;
}

QString LinkGroupSubject::getClassName() {
    return QString("LinkGroupSubject");
}

QJsonObject LinkGroupSubject::toJson() {
    QJsonObject items;
    items.insert("id", QString("%1").arg(this->id));
    items.insert("groupId", QString("%1").arg(this->groupId));
    items.insert("subjectId", QString("%1").arg(this->subjectId));
    items.insert("academicHours", QString("%1").arg(this->academicHours));

    return items;
}

void LinkGroupSubject::fromJson(QJsonObject items) {

    this->id = items.value("id").toString().toInt();
    this->groupId = items.value("groupId").toString().toInt();
    this->subjectId = items.value("subjectId").toString().toInt();
    this->academicHours = items.value("academicHours").toString().toInt();
}

QString LinkGroupSubject::toString() {
    return QString("id: %1, groupId: %2, subjectId: %3, academicHours: %4").arg(this->id).arg(this->groupId).arg(this->subjectId).arg(this->academicHours);
}

bool LinkGroupSubject::operator== (const LinkGroupSubject &object)
{
    return (
               (this->groupId == object.groupId || object.groupId != 0)
            && (this->subjectId == object.subjectId || object.subjectId == 0)
            && (this->academicHours == object.academicHours ||  object.academicHours == 0)
    );
}
