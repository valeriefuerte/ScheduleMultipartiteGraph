#ifndef LESSONTOJSON_H
#define LESSONTOJSON_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "models/groupstudents.h"
#include "models/lessontime.h"
#include "models/subject.h"
#include "Lesson.h"

class LessontoJson{
public:



    QHash<int,QString> receiveDay;


    QJsonObject toJson(QList<Lesson>);


    QList<Lesson> fromJson(QJsonObject mainJsonObject);

    GroupStudents fromJsonGr(QJsonObject items);
    Subject fromJsonSub(QJsonObject items);
    Cabinet fromJsonCab(QJsonObject items);
    LessonTime fromJsonLT(QJsonObject items);


};

QJsonObject LessontoJson::toJson(QList<Lesson> lesson) {
    //основной json object
    QJsonObject mainJsonObject;


    QJsonArray arGroup;
    QJsonArray arSubject;
    QJsonArray arCabinet;
    QJsonArray arLT;


    for (int i=0; i<lesson.size(); i++){
          arGroup.append(lesson[i]._group.toJson());
    }
    for (int i=0; i<lesson.size(); i++){
          arSubject.append(lesson[i]._subject.toJson());
    }
    for (int i=0; i<lesson.size(); i++){
          arCabinet.append(lesson[i]._cabinet.toJson());
    }
    for (int i=0; i<lesson.size(); i++){
          arLT.append(lesson[i]._lessonTime.toJson());
    }

    mainJsonObject.insert("_group",arGroup);
    mainJsonObject.insert("_subject",arSubject);
    mainJsonObject.insert("_cabinet",arCabinet);
    mainJsonObject.insert("_lessonTime",arLT);

    return mainJsonObject;

}
QList<Lesson> LessontoJson::fromJson(QJsonObject mainJsonObject){

    receiveDay[1]="Понедельник";
    receiveDay[2]="Вторник";
    receiveDay[3]="Среда";
    receiveDay[4]="Четверг";
    receiveDay[5]="Пятница";
    receiveDay[6]="Суббота";
    int size = mainJsonObject.value("_group").toArray().size();
    QList<Lesson> lessons;

    for (int i =0; i<size; i++){
        lessons.append(Lesson(fromJsonGr(mainJsonObject.value("_group").toArray().at(i).toObject()),fromJsonSub(mainJsonObject.value("_subject").toArray().at(i).toObject()),
                              fromJsonCab(mainJsonObject.value("_cabinet").toArray().at(i).toObject()),fromJsonLT(mainJsonObject.value("_lessonTime").toArray().at(i).toObject()),
                              receiveDay));
    }

    return lessons;
 }


GroupStudents LessontoJson::fromJsonGr(QJsonObject items) {
    GroupStudents group;

    group.id = items.value("id").toString().toInt();
    group.name = items.value("name").toString();
    return group;
}
Subject LessontoJson::fromJsonSub(QJsonObject items) {
    Subject subject;
    subject.id = items.value("id").toString().toInt();
    subject.name = items.value("name").toString();
    subject.subjectType = items.value("subjectType").toString().toInt();
    return subject;
}

Cabinet LessontoJson::fromJsonCab(QJsonObject items) {
    Cabinet cabinet;

    cabinet.id = items.value("id").toString().toInt();
    cabinet.number = items.value("number").toString().toInt();
    cabinet.floor = items.value("floor").toString().toInt();
    cabinet.building = items.value("building").toString().toInt();

    return cabinet;
}

LessonTime LessontoJson::fromJsonLT(QJsonObject items) {
    LessonTime lt;

    lt.id = items.value("id").toString().toInt();
    lt.parity = items.value("parity").toString().toInt();
    lt.dayOfWeek = items.value("dayOfWeek").toString().toInt();
    lt.time = QTime(items.value("hour").toString().toInt(), items.value("minute").toString().toInt(), 0, 0);

    return lt;
}



#endif // LESSONTOJSON_H
