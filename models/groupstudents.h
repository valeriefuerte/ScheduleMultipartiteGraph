#ifndef GROUPSTUDENTS_H
#define GROUPSTUDENTS_H

#include <QString>
#include "abstractnoderepository.h"

class GroupStudents : public abstractNodeRepository
{
public:
    GroupStudents(QString name = "");

    QString name;
};

#endif // GROUPSTUDENTS_H
