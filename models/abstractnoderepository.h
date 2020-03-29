#ifndef ABSTRACTNODEREPOSITORY_H
#define ABSTRACTNODEREPOSITORY_H
#include <QMap>
#include <QJsonObject>

class abstractNodeRepository
{
public:
    int id = 0;

    abstractNodeRepository();
    virtual QString getClassName() = 0;
    virtual void fromJson(QJsonObject) = 0;
    virtual QJsonObject toJson() = 0;
};

#endif // ABSTRACTNODEREPOSITORY_H
