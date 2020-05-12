#ifndef DIALOGWINDOWADDLINKGROUPSUBJECT_H
#define DIALOGWINDOWADDLINKGROUPSUBJECT_H
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include<QFormLayout>
#include <models/groupstudents.h>
#include <models/subject.h>
#include <models/repository/repositorytemplate.h>
#include <models/linkgroupsubject.h>
#include <models/linkgroupsubject.h>

class DialogAddLinkGroupSubject : public QDialog{
    Q_OBJECT
public:
    DialogAddLinkGroupSubject(QWidget* parent=0);
    void addLinkGroupSubject(int, int, RepositoryTemplate<GroupStudents>, RepositoryTemplate<Subject>);
    ~DialogAddLinkGroupSubject();

private:
    RepositoryTemplate<GroupStudents> receiveRepGroup;
    RepositoryTemplate<Subject> receiveRepSubject;
    RepositoryTemplate<LinkGroupSubject> repoLinkGrSub;

    int indexRSub, indexRGroup;
    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;

    QPushButton *applyButton;

    QLabel *nameGroup;
    QLabel *nameSubject;
    QLineEdit *academHours;
    int increment =0;

    void editDataRepoGroup(RepositoryTemplate<GroupStudents>);
    void editDataRepoSubject(RepositoryTemplate<Subject>);
private slots:
    void apply_clicked();
signals:
    void sendRepoGroupSubject(LinkGroupSubject,QString);
};

#endif // DIALOGWINDOWADDLINKGROUPSUBJECT_H
