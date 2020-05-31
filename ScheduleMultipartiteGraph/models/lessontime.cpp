#include "lessontime.h"

LessonTime::LessonTime(int parity, int dayOfWeek, QTime time)
{
    this->parity = parity;
    this->dayOfWeek = dayOfWeek;
    this->time = time;
}

LessonTime::LessonTime(int dayOfWeek, QTime time)
{
    this->parity = -1;
    this->dayOfWeek = dayOfWeek;
    this->time = time;
}

LessonTime::LessonTime(QTime time)
{
    this->parity = -1;
    this->dayOfWeek = -1;
    this->time = time;
}

LessonTime::LessonTime()
{
    this->parity = -1;
    this->dayOfWeek = -1;
    this->time = QTime(0,0,0,0);
}

QString LessonTime::getClassName() {
    return QString("LessonTime");
}

QJsonObject LessonTime::toJson() {
    QJsonObject items;
    items.insert("id", QString("%1").arg(this->id));
    items.insert("parity", QString("%1").arg(this->parity));
    items.insert("dayOfWeek", QString("%1").arg(this->dayOfWeek));
    items.insert("hour", QString("%1").arg(this->time.hour()));
    items.insert("minute", QString("%1").arg(this->time.minute()));

    return items;
}

void LessonTime::fromJson(QJsonObject items) {
    this->id = items.value("id").toString().toInt();
    this->parity = items.value("parity").toString().toInt();
    this->dayOfWeek = items.value("dayOfWeek").toString().toInt();
    this->time = QTime(items.value("hour").toString().toInt(), items.value("minute").toString().toInt(), 0, 0);
}

QString LessonTime::toString() {
    return QString("Четность: %1, день недели: %2, время: %3").arg(this->parity).arg(this->dayOfWeek).arg(this->time.toString());
//    return QString("id: %1, parity: %2, dayOfWeek: %3, time: %4").arg(this->id).arg(this->parity).arg(this->dayOfWeek).arg(this->time.toString());
}

bool LessonTime::operator== (const LessonTime &object)
{
    return (
                (this->parity == object.parity || object.parity == 0)
             && (this->dayOfWeek == object.dayOfWeek || object.dayOfWeek == 0)
             && (this->time == object.time ||  object.time == QTime(0,0,0,0))
    );
}
