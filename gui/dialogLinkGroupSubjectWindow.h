#ifndef DIALOGLINKGROUPSUBJECTWINDOW_H
#define DIALOGLINKGROUPSUBJECTWINDOW_H
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include<QFormLayout>
#include <QTableView>
#include <models/tablelistmodel.h>
#include <models/groupstudents.h>
#include <models/subject.h>
#include <models/repository/repositorytemplate.h>
#include <models/linkgroupsubject.h>
#include "dialogAddlinkGroupSubject.h"


class DialogLinkGroupSubjectWindow : public QDialog{
    Q_OBJECT
public:
    RepositoryTemplate<GroupStudents> repoRecGroupStudent;
    RepositoryTemplate<Subject> repoRecSubject;

    void receiveGroup(int,QStringList,RepositoryTemplate<GroupStudents>,RepositoryTemplate<Subject>);
    DialogLinkGroupSubjectWindow(QWidget* parent=0);

private:
    int indexGroup,indexSubject;

    DialogAddLinkGroupSubject *dialogLinkGS;
    RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubjects;

    QStringList *list_link_subject;
    QStringList *list_s;

    QLabel *label_allSub;
    QLabel *label_link;

    QTableView *table_subject;
    QTableView *table_link_subject;


    TableListModel *sub_model;
    TableListModel *link_sub_model;
    QGridLayout *gridLayout;


   void visualRows(QTableView *table, TableListModel *model);
   void clearTableView();

private slots:
 void slotLinkSubject_GroupAddRecord();
 void customLinkGroupSubjectMenuRequested(const QPoint &pos);
 void receiveRepoGroupSubject(RepositoryTemplate<LinkGroupSubject>,QString);
};

#endif // DIALOGLINKGROUPSUBJECTWINDOW_H
