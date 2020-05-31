#ifndef GRAPH_H
#define GRAPH_H
#include <QList>
#include <QMap>
#include <QSet>
#include <QPair>
#include <QMapIterator>
#include <QtAlgorithms>

#include <cmath>

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
    void firstStep();
    void initWeights();

    // Списки смежности
    QMap<int, QList<QPair<int, float>>> subjects;
    QMap<int, QList<QPair<int, float>>> groupsStudents;
    QMap<int, QList<QPair<int, float>>> cabinets;
    QMap<int, QList<QPair<int, float>>> times;

    // Список всех ребер
    QList<QPair<int, int>> groups_subjects;
    QList<QPair<int, int>> subjects_cabinets;
    QList<QPair<int, int>> cabinets_times;
//    QMap<int, QMap<int, QMap<int, int>>> e;


    // Список всех используемых ребер
//    QList<QPair<int, int>> used_groups_subjects;
//    QList<QPair<int, int>> used_subjects_cabinets;
//    QList<QPair<int, int>> used_cabinets_times;
    QList<QPair<int, int>> used_edges;
//    QMap<int, float> w1;
//    QMap<int, float> w2;

    QMap<int, QMap<QString, QMap<int, float>>> weights;

    // Список всех используемых ребер
//    QList<float> weights_groups_subjects;
//    QList<float> weights_subjects_cabinets;
//    QList<float> weights_cabinets_times;
//    QMap<int, QMap<QString, QList<float>>> weights;

public:
    Graph();
    Graph(
        RepositoryTemplate<Cabinet> repoCabinets,
        RepositoryTemplate<GroupStudents> repoGroupStudents,
        RepositoryTemplate<LessonTime> repoLessonTime,
        RepositoryTemplate<Subject> repoSubjects,
        RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubject
    );

    void show();
    void showConnects();
    QList<QList<int>> fit();

    //Репозитории
    RepositoryTemplate<Cabinet> repoCabinets;
    RepositoryTemplate<GroupStudents> repoGroupStudents;
    RepositoryTemplate<LessonTime> repoLessonTime;
    RepositoryTemplate<Subject> repoSubjects;
    RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubject;
};

#endif // GRAPH_H
