#ifndef LESSONTIME_H
#define LESSONTIME_H

#include <QDateTime>
#include <QDate>
#include <QTime>
#include "abstractnoderepository.h"

class LessonTime : public abstractNodeRepository
{
public:
    int parity;
    int dayOfWeek;
    QTime time;

    LessonTime(int parity, int dayOfWeek, QTime time);
    LessonTime(int dayOfWeek, QTime time);
    LessonTime(QTime time);
    LessonTime();

    virtual QString getClassName();
    virtual void fromJson(QJsonObject);
    virtual QJsonObject toJson();
    QString toString();

    bool operator== (const LessonTime &object);
};

#endif // LESSONTIME_H
