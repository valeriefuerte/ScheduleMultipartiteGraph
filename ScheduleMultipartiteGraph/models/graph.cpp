#include "graph.h"

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

    this->initGraph();
}

void Graph::initGraph()
{
    for (int i=0; i < this->repoLinkGroupSubject.getAmount(); ++i) {
        LinkGroupSubject linkGroupSubject = this->repoLinkGroupSubject.getByIndex(i);
        if (this->groupsStudents.count(linkGroupSubject.groupId) > 0) {
            QList<int> tmp = *this->groupsStudents.find(linkGroupSubject.groupId);
            tmp.append(linkGroupSubject.subjectId);
            this->groupsStudents.remove(linkGroupSubject.groupId);
            this->groupsStudents.insert(linkGroupSubject.groupId, tmp);
        } else {
            QList<int> tmp = {linkGroupSubject.subjectId};
            this->groupsStudents.insert(linkGroupSubject.groupId, tmp);
        }
    }

    for (int i=0; i < this->repoSubjects.getAmount(); ++i) {
        Subject subject = this->repoSubjects.getByIndex(i);
        QList<int> tmp = {};
        this->subjects.insert(subject.id, tmp);
    }

    for (int i=0; i < this->repoCabinets.getAmount(); ++i) {
        Cabinet cabinet = this->repoCabinets.getByIndex(i);
        QList<int> tmp = {};
        this->subjects.insert(cabinet.id, tmp);
    }

    for (int i=0; i < this->repoLessonTime.getAmount(); ++i) {
        LessonTime times = this->repoLessonTime.getByIndex(i);
        QList<int> tmp = {};
        this->subjects.insert(times.id, tmp);
    }

}

void Graph::fit()
{
     this->firstStep();
}

void Graph::firstStep()
{
    QList<int> keys = this->groupsStudents.keys();
    for (int key : keys) {
        auto gr = this->groupsStudents.find(key);
        QList<int> groupStudents = *gr;

        auto sub = groupStudents.begin() + rand() % groupStudents.size();
        int subject = *sub;

        auto cab = this->repoCabinets.getAll().begin() + rand() % this->repoCabinets.getAll().size();
        Cabinet cabinet = *cab;

        QList<int> tmp = { cabinet.id };
        this->subjects.remove(subject);
        this->subjects.insert(subject, tmp);

        // Чтобы не было повторений
        while (true) {
            auto t = this->repoLessonTime.getAll().begin() + rand() % this->repoLessonTime.getAll().size();
            LessonTime time = *t;

            QList<int> cabtime = *this->cabinets.find(cabinet.id);
            if(cabtime.count(time.id) == 0) {
                tmp = { time.id };
                this->cabinets.remove(cabinet.id);
                this->cabinets.insert(cabinet.id, tmp);
            }
        };
    }
}

