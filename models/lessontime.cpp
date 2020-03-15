#include "lessontime.h"

LessonTime::LessonTime(QTime time, QDate date)
{
    this->datetime = QDateTime(date, time);
}

LessonTime::LessonTime(QTime time)
{
    this->datetime = QDateTime(QDate(0,0,0), time);
}

LessonTime::LessonTime()
{
    this->datetime = QDateTime(QDate(0,0,0), QTime(0,0,0,0));
}
