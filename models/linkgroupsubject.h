#ifndef LINKGROUPSUBJECT_H
#define LINKGROUPSUBJECT_H

#include "abstractnoderepository.h"

class LinkGroupSubject : public abstractNodeRepository
{
public:
    int groupId;
    int subjectId;
    int academicHours;

    LinkGroupSubject();

    virtual QString getClassName();
    virtual void fromJson(QJsonObject);
    virtual QJsonObject toJson();
    QString toString();

    bool operator == (const LinkGroupSubject &object);
};

#endif // LINKGROUPSUBJECT_H
