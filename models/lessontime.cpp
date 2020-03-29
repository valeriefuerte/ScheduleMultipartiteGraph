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
    this->id = items.value("id").toInt();
    this->parity = items.value("parity").toInt();
    this->dayOfWeek = items.value("dayOfWeek").toInt();
    this->time = QTime(items.value("hour").toInt(), items.value("minute").toInt(), 0, 0);
}
