#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include "abstractnoderepository.h"

class Subject : public abstractNodeRepository
{
public:
    QString name;
    int subjectType;

    Subject(QString name = "");
    Subject(QString name = "", int subjectType = 0);
    virtual QString getClassName();
    virtual void fromJson(QJsonObject);
    virtual QJsonObject toJson();
    QString toString();

    bool operator== (const Subject &object);
};

#endif // SUBJECT_H
