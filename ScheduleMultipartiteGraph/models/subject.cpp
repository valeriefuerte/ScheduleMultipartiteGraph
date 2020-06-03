#include "subject.h"

Subject::Subject(QString name)
{
    this->name = name;
    this->subjectType = 0;
}

Subject::Subject(QString name, int subjectType)
{
    this->name = name;
    this->subjectType = subjectType;
}

QString Subject::getClassName() {
    return QString("Subject");
}

QJsonObject Subject::toJson() {
    QJsonObject items;
    items.insert("id", QString("%1").arg(this->id));
    items.insert("name", QString("%1").arg(this->name));
    items.insert("subjectType", QString("%1").arg(this->subjectType));
    return items;
}

void Subject::fromJson(QJsonObject items) {
    this->id = items.value("id").toString().toInt();
    this->name = items.value("name").toString();
    this->subjectType = items.value("subjectType").toString().toInt();
}

QString Subject::toString() {
    return QString("%1(%2)").arg(this->name).arg(this->subjectType);
//    return QString("id: %1, name: %2, subjectType: %3").arg(this->id).arg(this->name).arg(this->subjectType);
}

bool Subject::operator== (const Subject &object)
{
    return (
            (this->name == object.name || object.name == "")
         && (this->subjectType == object.subjectType || object.subjectType == 0)
    );
}
