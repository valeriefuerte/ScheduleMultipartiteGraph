#ifndef LESSONTIME_H
#define LESSONTIME_H

#include <QDateTime>
#include <QDate>
#include <QTime>
#include "abstractnoderepository.h"

class LessonTime : public abstractNodeRepository
{
public:
    LessonTime(QTime time, QDate date);
    LessonTime(QTime time);
    LessonTime();

    QDateTime datetime;
};

#endif // LESSONTIME_H
