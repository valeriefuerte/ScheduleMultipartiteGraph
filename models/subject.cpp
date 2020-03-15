#include "subject.h"

Subject::Subject(int id, QString name)
{
    this->id = id;
    this->name = name;
}

Subject::Subject()
{
    this->id = 0;
    this->name = "";
}
