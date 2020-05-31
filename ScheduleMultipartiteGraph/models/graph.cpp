#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(
    RepositoryTemplate<Cabinet> repoCabinets,
    RepositoryTemplate<GroupStudents> repoGroupStudents,
    RepositoryTemplate<LessonTime> repoLessonTime,
    RepositoryTemplate<Subject> repoSubjects,
    RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubject
)
{
    this->repoCabinets = repoCabinets;
    this->repoGroupStudents = repoGroupStudents;
    this->repoLessonTime = repoLessonTime;
    this->repoSubjects = repoSubjects;
    this->repoLinkGroupSubject = repoLinkGroupSubject;
//    this->initGraph();
}

void Graph::initGraph()
{
    for (int i=0; i < this->repoLinkGroupSubject.getAmount(); ++i) {
        LinkGroupSubject linkGroupSubject = this->repoLinkGroupSubject.getByIndex(i);
        QPair<int, int> item;

        item.first = linkGroupSubject.groupId;
        item.second = linkGroupSubject.subjectId;

        this->groups_subjects.append(item);
    }

    for (int i=0; i < this->repoSubjects.getAmount(); ++i) {
        Subject subject = this->repoSubjects.getByIndex(i);
        QList<QPair<int, float>> tmp = {};
        this->subjects.insert(subject.id, tmp);
    }

    for (int i=0; i < this->repoCabinets.getAmount(); ++i) {
        Cabinet cabinet = this->repoCabinets.getByIndex(i);
        QList<QPair<int, float>> tmp = {};
        this->cabinets.insert(cabinet.id, tmp);
    }

    for (int i=0; i < this->repoLessonTime.getAmount(); ++i) {
        LessonTime times = this->repoLessonTime.getByIndex(i);
        QList<QPair<int, float>> tmp = {};
        this->times.insert(times.id, tmp);
    }

}

//void Graph::initGraph()
//{
//    for (int i=0; i < this->repoLinkGroupSubject.getAmount(); ++i) {
//        LinkGroupSubject linkGroupSubject = this->repoLinkGroupSubject.getByIndex(i);
//        QPair<int, float> item;

//        item.first = linkGroupSubject.subjectId;
//        item.second = 0;

//        for (int j = 0; j < linkGroupSubject.academicHours; ++j) {
//            auto it = this->groupsStudents.find(linkGroupSubject.groupId);
//            if (it != this->groupsStudents.end()) {
//                auto tmp = *it;
//                tmp.append(item);
//                this->groupsStudents.remove(linkGroupSubject.groupId);
//                this->groupsStudents.insert(linkGroupSubject.groupId, tmp);
//            } else {
//                QList<QPair<int, float>> tmp = {item};
//                this->groupsStudents.insert(linkGroupSubject.groupId, tmp);
//            }
//        }
//    }

//    qDebug() << endl;

//    for (int i=0; i < this->repoSubjects.getAmount(); ++i) {
//        Subject subject = this->repoSubjects.getByIndex(i);
//        QList<QPair<int, float>> tmp = {};
//        this->subjects.insert(subject.id, tmp);
//    }

//    qDebug() <<  this->repoCabinets.getAmount() << endl;
//    for (int i=0; i < this->repoCabinets.getAmount(); ++i) {
//        Cabinet cabinet = this->repoCabinets.getByIndex(i);
//        QList<QPair<int, float>> tmp = {};
//        this->cabinets.insert(cabinet.id, tmp);
//    }

//    for (int i=0; i < this->repoLessonTime.getAmount(); ++i) {
//        LessonTime times = this->repoLessonTime.getByIndex(i);
//        QList<QPair<int, float>> tmp = {};
//        this->times.insert(times.id, tmp);
//    }

//}

QList<QList<int>> Graph::fit()
{
    RepositoryTemplate<Cabinet> cabinets = this->repoCabinets;
    RepositoryTemplate<LessonTime> times = this->repoLessonTime;

    QMap<int, QList<QPair<int, int>>> ways;

    QList<QPair<int, int>> used_edges_local;
    QList<int> used_times;

    QList<QPair<int, int>> edges;
    QPair<int, int> edge;

    QList<QPair<int, float>> cabinets_w;
    QList<QPair<int, float>> times_w;

    QPair<int, float> pair;
    int k;
    int r;

    for (Cabinet cab : cabinets.getAll()) {
        edge.first = cab.id;
        for (LessonTime time : times.getAll()) {
            edge.second = time.id;
            edges.append(edge);
        }
    }

    for (GroupStudents group : this->repoGroupStudents) {
        cabinets_w.clear();
        times_w.clear();
        used_times.clear();
        used_edges_local.clear();

        auto links_subjects = this->repoLinkGroupSubject.getByParameters(LinkGroupSubject(group.id,-1,-1));

        srand(group.id+time(0));

        r = rand() % links_subjects.size();
        LinkGroupSubject start_link = links_subjects[r];

        r = rand() % cabinets.getAmount();
        Cabinet start_cabinet = cabinets.getByIndex(r);

        r = rand() % times.getAmount();
        LessonTime start_time = times.getByIndex(r);

        qSort(edges.begin(), edges.end(), [this, start_cabinet, start_time](QPair<int, int>& a, QPair<int, int>& b) {
            Cabinet cab1 = this->repoCabinets.getById(a.first);
            Cabinet cab2 = this->repoCabinets.getById(b.first);
            LessonTime time1 = this->repoLessonTime.getById(a.second);
            LessonTime time2 = this->repoLessonTime.getById(b.second);
            float c1 = sqrt(pow(cab1.number - start_cabinet.number, 2) + pow(cab1.floor - start_cabinet.floor, 2) + pow(cab1.building - start_cabinet.building, 2));
            float c2 = sqrt(pow(cab2.number - start_cabinet.number, 2) + pow(cab2.floor - start_cabinet.floor, 2) + pow(cab2.building - start_cabinet.building, 2));
            float t1 = sqrt(pow(time1.dayOfWeek - start_time.dayOfWeek,2) + pow(time1.parity - start_time.parity,2) + pow((start_time.time.msecsSinceStartOfDay()/8640000+start_time.dayOfWeek*100) - (time1.time.msecsSinceStartOfDay()/8640000+time1.dayOfWeek*100),2));
            float t2 = sqrt(pow(time2.dayOfWeek - start_time.dayOfWeek,2) + pow(time2.parity - start_time.parity,2) + pow((start_time.time.msecsSinceStartOfDay()/8640000+start_time.dayOfWeek*100) - (time2.time.msecsSinceStartOfDay()/8640000+time2.dayOfWeek*100),2));
            return c1 + t1 < c2 + t2;
        });

        for (LinkGroupSubject link : links_subjects) {
            for (int i = 0, amount = link.academicHours; i < amount; ++i) {

                for (k = 0; used_times.count(edges[k].second) != 0; ++k);

                pair = edges[k];
                edges.removeAt(k);

                used_times.append(pair.second);
                used_edges_local.append(pair);
            }
        }

        ways.insert(group.id, used_edges_local);
    }

    QList<QList<int>> result;
    QList<int>way;

    for (LinkGroupSubject link : this->repoLinkGroupSubject) {
       k=0;
       for (int i = 0; i < link.academicHours; ++i) {
            way.append(link.groupId);
            way.append(link.subjectId);
            way.append(ways[link.groupId][k].first);
            way.append(ways[link.groupId][k].second);
            result.append(way);
            ++k;
        }
    }

    return result;
}

void Graph::firstStep()
{
    // Проходимся по всем группам учащихся
    QList<int> keys = this->groupsStudents.keys();
    for (int key : keys) {
        srand(time(0));

        // Получаем объект группы студентов
        QList<QPair<int, float>> groupStudents = *this->groupsStudents.find(key);

        // Выбираем случайный предмет
        int r = rand() % groupStudents.size();
        QPair<int, float> subject = groupStudents[r];

        // Выбираем случайный кабинет
        r = rand() % this->repoCabinets.getAmount();
        auto cabinet = this->repoCabinets.getByIndex(r);

        // Закрепляем за предметом кабинет
        QPair<int, float> item;
        item.first = cabinet.id;
        item.second = 0;

        QList<QPair<int, float>> tmp = { item };
        this->subjects.remove(subject.first);
        this->subjects.insert(subject.first, tmp);

        // Чтобы не было повторений
        while (true) {
            srand(time(0));
            int r = rand() % this->repoLessonTime.getAmount();
            auto time = this->repoLessonTime.getByIndex(r);

            auto cabtime = this->cabinets[cabinet.id];
            QPair<int, float> item;
            item.first = time.id;
            item.second = 0;
            if(cabtime.count(item) == 0) {
                tmp = { item };
                this->cabinets.remove(cabinet.id);
                this->cabinets.insert(cabinet.id, tmp);
                break;
            }
        };
    }
}

void Graph::initWeights()
{
//    this->groupsStudents.va

}

void Graph::showConnects() {
    QMapIterator<int, QList<QPair<int, float>>> it(this->groupsStudents);

    while (it.hasNext()) {
        it.next();
        auto subjects = it.value();
        for (auto subject : subjects) {
            auto cabinets = this->subjects[subject.first];
            for (auto cabinet : cabinets) {
                auto times = this->cabinets[cabinet.first];
                for (auto time : times) {
                    GroupStudents g = this->repoGroupStudents.getById(it.key());
                    Subject s = this->repoSubjects.getById(subject.first);
                    Cabinet c = this->repoCabinets.getById(cabinet.first);
                    LessonTime t = this->repoLessonTime.getById(time.first);

                    qDebug() << g.toString().toLocal8Bit().data()  << " -> " << s.toString().toLocal8Bit().data() << " -> " << c.toString().toLocal8Bit().data() << " -> "  << t.toString().toLocal8Bit().data() << endl;
                }
            };
        }
    }
}

void Graph::show()
{
    for (int i=0; i < this->repoCabinets.getAmount(); ++i) {
        Cabinet cabinet = this->repoCabinets.getByIndex(i);
        qDebug() << cabinet.toString() << endl;
    }
    qDebug() << this->repoCabinets.getAmount() << endl;

    for (int i=0; i < this->repoSubjects.getAmount(); ++i) {
        Subject subject = this->repoSubjects.getByIndex(i);
        qDebug() << subject.toString() << endl;
    }
    qDebug() << this->repoSubjects.getAmount() << endl;

    for (int i=0; i < this->repoLessonTime.getAmount(); ++i) {
        LessonTime lessonTime = this->repoLessonTime.getByIndex(i);
        qDebug() << lessonTime.toString() << endl;
    }
    qDebug() << this->repoLessonTime.getAmount() << endl;

    for (int i=0; i < this->repoGroupStudents.getAmount(); ++i) {
        GroupStudents groupStudents = this->repoGroupStudents.getByIndex(i);
        qDebug() << groupStudents.toString() << endl;
    }
    qDebug() << this->repoGroupStudents.getAmount() << endl;

    for (int i=0; i < this->repoLinkGroupSubject.getAmount(); ++i) {
        LinkGroupSubject linkGroupSubject = this->repoLinkGroupSubject.getByIndex(i);
        qDebug() << linkGroupSubject.toString() << endl;
    }
    qDebug() << this->repoLinkGroupSubject.getAmount() << endl;
}
