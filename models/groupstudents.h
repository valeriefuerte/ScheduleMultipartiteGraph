#ifndef GROUPSTUDENTS_H
#define GROUPSTUDENTS_H

#include <QString>
#include "abstractnoderepository.h"

class GroupStudents : public abstractNodeRepository
{
public:
    QString name;

    GroupStudents(QString name = "");
    virtual QString getClassName();
    virtual void fromJson(QJsonObject);
    virtual QJsonObject toJson();
    QString toString();
};

#endif // GROUPSTUDENTS_H
