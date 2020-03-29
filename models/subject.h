#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include "abstractnoderepository.h"

class Subject : public abstractNodeRepository
{
public:
    QString name;

    Subject(QString name = "");
    virtual QString getClassName();
    virtual void fromJson(QJsonObject);
    virtual QJsonObject toJson();
    QString toString();
};

#endif // SUBJECT_H
