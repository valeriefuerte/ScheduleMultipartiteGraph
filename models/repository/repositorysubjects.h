#ifndef REPOSITORYSUBJECTS_H
#define REPOSITORYSUBJECTS_H

#include <QList>
#include "../cabinet.h"

class repositorySubjects
{
private:
    QList<Cabinet> cabinets;
public:
    repositorySubjects();
    ~repositorySubjects();
    bool add();
    bool remove();
    bool update();
    Cabinet getById(int id);
    QList<Cabinet> getAll();
};

#endif // REPOSITORYSUBJECTS_H
