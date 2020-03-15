#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>

class Subject
{
public:
    Subject(QString name);
    Subject();
//    ~Subject();

    int id;
    QString name;
};

#endif // SUBJECT_H
