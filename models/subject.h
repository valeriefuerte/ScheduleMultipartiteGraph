#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include "abstractnoderepository.h"

class Subject : public abstractNodeRepository
{
public:
    Subject(QString name = "");

    QString name;
};

#endif // SUBJECT_H
