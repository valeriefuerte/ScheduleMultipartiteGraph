#ifndef LESSON_H
#define LESSON_H
#include <QString>
#include <QVector>
#include "models/cabinet.h"
#include "models/groupstudents.h"
#include "models/subject.h"
#include "models/lessontime.h"
#include <QHash>
struct Lesson{
    Lesson(GroupStudents group, Subject subject,
           Cabinet cabinet,LessonTime lessonTime,QHash<int,QString> receiveDay):

        _group(group), _subject(subject),_cabinet(cabinet),_lessonTime(lessonTime),_receiveDay(receiveDay) {
    }
    QVector<QString> coll = {"Группа", "Предмет","Кабинет","Этаж","Корпус","Четность","День недели","Время"};
    GroupStudents _group;
    Subject _subject;
    Cabinet _cabinet;
    LessonTime _lessonTime;
    QHash<int,QString> _receiveDay;

};

#endif // LESSON_H
