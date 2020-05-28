#ifndef GRAPH_H
#define GRAPH_H
#include <QList>
#include <QMap>
#include <QSet>

#include "models/cabinet.h"
#include "models/groupstudents.h"
#include "models/lessontime.h"
#include "models/subject.h"
#include "models/linkgroupsubject.h"
#include "models/repository/repositorytemplate.h"

class Graph
{
private:
    void initGraph();
    void fit();
    void firstStep();

    // Списки смежности
    QMap<int, QList<int>> subjects;
    QMap<int, QList<int>> groupsStudents;
    QMap<int, QList<int>> cabinets;
    QMap<int, QList<int>> times;
public:
    Graph(
        RepositoryTemplate<Cabinet> repoCabinets,
        RepositoryTemplate<GroupStudents> repoGroupStudents,
        RepositoryTemplate<LessonTime> repoLessonTime,
        RepositoryTemplate<Subject> repoSubjects,
        RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubject
    );

    //Репозитории
    RepositoryTemplate<Cabinet> repoCabinets;
    RepositoryTemplate<GroupStudents> repoGroupStudents;
    RepositoryTemplate<LessonTime> repoLessonTime;
    RepositoryTemplate<Subject> repoSubjects;
    RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubject;
};

#endif // GRAPH_H
