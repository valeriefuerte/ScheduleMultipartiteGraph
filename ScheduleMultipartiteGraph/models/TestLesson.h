#ifndef TESTLESSON_H
#define TESTLESSON_H
//DeleteMeAfter
#include <QString>
#include <QVector>

//example
//QList<Lesson> planetList;
//planetList.append(Lesson("Jupiter", 23.1, 1.326));
//planetList.append(Lesson("Saturn", 9.0, 0.687));
//planetList.append(Lesson("Uranus", 	8.7, 1.271));
//planetList.append(Lesson("Neptune", 11.0, 1.638));
//planetList.append(Lesson("Earth", 9.8, 5.514));
//planetList.append(Lesson("Venus", 8.9, 5.243));
//planetList.append(Lesson("Mars", 3.7, 3.933));
//planetList.append(Lesson("Mercury", 3.7, 5.427));

//ScheduleTableAbstractModule *model = new ScheduleTableAbstractModule(planetList);
//ScheduleWidget *v = new ScheduleWidget (model,this);
//ui->tabWidget->addTab(v,"Расписание");


struct TestLesson{
    TestLesson(const QString& name = QString(), double data1 = 0.0,
           double data2 = 0.0):
        m_name(name), m_data1(data1), m_data2(data2){
    }
    QVector<QString> coll = {"Name", "data1","data2"};
    QString m_name;
    double m_data1;
    double m_data2;
};

#endif // TESTLESSON_H
