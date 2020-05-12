#include "dialogAddlinkGroupSubject.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include <qvalidator.h>
#include<QFormLayout>
#include <models/repository/repositorytemplate.h>
#include <models/groupstudents.h>
#include <models/subject.h>

DialogAddLinkGroupSubject::DialogAddLinkGroupSubject(QWidget* parent): QDialog(parent)
{
    this->setWindowTitle("Добавление предмета");
    nameGroup = new QLabel();
    nameSubject = new QLabel();

    applyButton = new QPushButton("OK");
    applyButton->setMaximumWidth(80);

    academHours = new QLineEdit();
    academHours->setValidator(new QIntValidator(0,500,this));

    formLayout = new QFormLayout();

    btnLayout=new QVBoxLayout();
    btnLayout->addWidget(applyButton);

    formLayout->addRow("Группа:",nameGroup);
    formLayout->addRow("Предмет:",nameSubject);
    formLayout->addRow("Академические часы",academHours);
    formLayout->addWidget(applyButton);
    setLayout(formLayout);
    connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
}
DialogAddLinkGroupSubject::~DialogAddLinkGroupSubject(){
    delete this;
}
void DialogAddLinkGroupSubject::addLinkGroupSubject(int indexGroup,int indexSubject,
                                   RepositoryTemplate<GroupStudents> repoGroupStud, RepositoryTemplate<Subject> repoSubject ){
    indexRGroup = indexGroup;
    indexRSub = indexSubject;

    editDataRepoGroup(repoGroupStud);
    editDataRepoSubject(repoSubject);

        /*qDebug()<<"RepoGroupStudents: ";
        for (int i = 0; i<repoGroupStud.getAmount(); i++){
            qDebug()<<repoGroupStud.getByIndex(i).name;
        }
        qDebug()<<"RepoRecGroupStudents: ";
        for (int i = 0; i<receiveRepGroup.getAmount(); i++){
            qDebug()<<receiveRepGroup.getByIndex(i).name;
        }
        qDebug()<<"RepoSubjects: ";
       for (int i = 0; i<repoSubject.getAmount(); i++){
           qDebug()<<repoSubject.getByIndex(i).name;
       }
       qDebug()<<"RepoRecSubjects: ";
       for (int i = 0; i<receiveRepSubject.getAmount(); i++){
           qDebug()<<receiveRepSubject.getByIndex(i).name;
       }*/

           /*qDebug()<<"RepoSubject: "<<repoSubjects.getAmount()<<"RepoSubject: "<<repoRecSubject.getAmount();
           for (int i =0; i<repoRecSubject.getAmount(); i++){
                qDebug()<<repoRecSubject.getById(i).name;
          }*/

    nameGroup->setText(repoGroupStud.getById(repoGroupStud.getByIndex(indexGroup).id).name);
    nameSubject->setText(repoSubject.getById(repoSubject.getByIndex(indexRSub).id).name);


}
void DialogAddLinkGroupSubject::apply_clicked(){

    int academic= academHours->text().toInt();
    repoLinkGrSub.add(LinkGroupSubject(receiveRepGroup.getById(receiveRepGroup.getByIndex(indexRGroup).id).id,
                     receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).id, academic));
    for (int i =0; i<repoLinkGrSub.getAmount(); i++){
        qDebug()<<"Link"<<repoLinkGrSub.getById(i).groupId<<repoLinkGrSub.getById(i).subjectId<<repoLinkGrSub.getById(i).academicHours;
    }
   emit sendRepoGroupSubject(repoLinkGrSub.getById(repoLinkGrSub.getByIndex(increment).id),receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).name);
   increment++;
   academHours->clear();
   this->close();
 }

void DialogAddLinkGroupSubject::editDataRepoGroup(RepositoryTemplate<GroupStudents> repoGroupStudents){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
    if (receiveRepGroup.getAmount()==0){
        for (int i =0; i<repoGroupStudents.getAmount(); i++){
            receiveRepGroup.add(repoGroupStudents.getById(i));
        }

    }else
          if (repoGroupStudents.getAmount()>receiveRepGroup.getAmount()){
            int raz = repoGroupStudents.getAmount()-receiveRepGroup.getAmount();
            int addE = receiveRepGroup.getAmount();
            for (int i =0; i<raz; i++){
                receiveRepGroup.add(repoGroupStudents.getById(repoGroupStudents.getByIndex(addE).id));
                ++addE;
            }
    }else
          if (repoGroupStudents.getAmount()<receiveRepGroup.getAmount()){
            int raz = receiveRepGroup.getAmount()-repoGroupStudents.getAmount();
            int delE = receiveRepGroup.getAmount()-1;
            for (int i =0; i<raz; i++){
                receiveRepGroup.removeByIndex(delE);
            --delE;
            }
    }
    else
         if (repoGroupStudents.getAmount()==receiveRepGroup.getAmount()){
            for (int i =0; i<repoGroupStudents.getAmount(); i++){
                if (repoGroupStudents.getByIndex(i).name!=receiveRepGroup.getByIndex(i).name){
                    receiveRepGroup.update(repoGroupStudents.getById(repoGroupStudents.getByIndex(i).id).id,repoGroupStudents.getByIndex(i).name);
                }
            }
          }
}

void DialogAddLinkGroupSubject::editDataRepoSubject(RepositoryTemplate<Subject> repoSubjects){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
    if (receiveRepSubject.getAmount()==0){
        for (int i =0; i<repoSubjects.getAmount(); i++){
            receiveRepSubject.add(repoSubjects.getByIndex(i));
        }

    }else
          if (repoSubjects.getAmount()>receiveRepSubject.getAmount()){
            int raz = repoSubjects.getAmount()-receiveRepSubject.getAmount();
            int addE = receiveRepSubject.getAmount();
            for (int i =0; i<raz; i++){
                receiveRepSubject.add(repoSubjects.getById(repoSubjects.getByIndex(addE).id));
                ++addE;
            }
    }else
          if (repoSubjects.getAmount()<receiveRepSubject.getAmount()){
            int raz = receiveRepSubject.getAmount()-repoSubjects.getAmount();
            int delE = receiveRepSubject.getAmount()-1;
            for (int i =0; i<raz; i++){
                receiveRepSubject.removeByIndex(delE);
            --delE;
            }
    }
    else
         if (repoSubjects.getAmount()==receiveRepSubject.getAmount()){
            for (int i =0; i<repoSubjects.getAmount(); i++){
                if (repoSubjects.getByIndex(i).name!=receiveRepSubject.getByIndex(i).name){
                    receiveRepSubject.update(repoSubjects.getById(repoSubjects.getByIndex(i).id).id,repoSubjects.getByIndex(i).name);
                }
            }
          }
  }


