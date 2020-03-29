#ifndef CABINET_H
#define CABINET_H

#include "abstractnoderepository.h"

class Cabinet : public abstractNodeRepository
{
private:
    static bool validation(int id, int number, int floor, int building);
public:
    int number;
    int floor;
    int building;

    Cabinet(int number=0, int floor=0, int building=0);
    virtual QString getClassName();
    virtual void fromJson(QJsonObject);
    virtual QJsonObject toJson();
};

#endif // CABINET_H
